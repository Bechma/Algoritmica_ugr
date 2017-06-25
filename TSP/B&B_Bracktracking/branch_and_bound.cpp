//
// COMPILAR CON g++ -std=c++11 -Ofast -o ejecutable branch_and_bound.cpp
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <queue>
#include "nodo.cpp"
#include <ctime>
using namespace std;

bool no_contiene(int n, const vector<int> & solucion_cota) {
	for(int i = 0; i < solucion_cota.size(); i++)
		if(solucion_cota[i] == n)
			return false;
	return true;
}

float greedy(const vector<vector<float>> & matriz) {
	vector<int> sol;
	sol.push_back(0);
	sol.push_back((int)matriz.size()/2);
	sol.push_back((int)matriz.size()-1);
	float minimo;

	for(int i = 1; i < matriz.size(); i++){
		if(no_contiene(i, sol)){
			minimo = 123123123;
			int pos = -1;
			for(int j = 0; j < sol.size(); j++){
				vector<int> auxiliar(sol);
				auto it = auxiliar.begin()+j;
				auxiliar.insert(it, i);
				float coste = 0;
				for(int k = 0; k < auxiliar.size()-1; k++)
					coste += matriz[auxiliar[k]][auxiliar[k+1]];
				coste += matriz[auxiliar.back()][auxiliar.front()];
				if(coste < minimo){
					minimo = coste;
					pos = j;
				}
			}
			sol.insert(sol.begin()+pos, i);
		}
	}
	return minimo;
}

int main (int argc, char *argv[]){
	if(argc != 2){
		cout << argv[0] << " ulysses16.tsp" << endl;
		return 1;
	}


	// CREAR MATRIZ ADYACENCIA

	fstream f(argv[1]);
	string s, s2;
	f >> s;
	f >> s;
	int tamanio = stoi(s);
	vector<pair<float,float>> numeros;
	vector<float> vminimo;
	for(int i = 0; i < tamanio; i++){
		f >> s;
		f >> s;
		f >> s2;
		numeros.push_back(make_pair(stof(s), stof(s2)));
	}
	f.close();
	vector<vector<float>> matriz_adyacencia((unsigned )tamanio, vector<float>((unsigned )tamanio));

	for(int i = 0; i < tamanio; i++){
		float minimo = 123123123;
		for(int j = 0; j < tamanio; j++){
			if(i == j)
				matriz_adyacencia[i][j] = 0;
			else
				matriz_adyacencia[i][j] = sqrt((numeros[i].first-numeros[j].first)*(numeros[i].first-numeros[j].first)
				                               + (numeros[i].second-numeros[j].second)*(numeros[i].second-numeros[j].second) );
			if(i != j && minimo > matriz_adyacencia[i][j])
				minimo = matriz_adyacencia[i][j];
		}
		vminimo.push_back(minimo);
	}


	/*
	for(auto & i : matriz_adyacencia){
		for(int j = 0; j < matriz_adyacencia.size(); j++)
			cout << i[j] << " ";
		cout << endl;
	}
	*/
	// FIN CREACION MATRIZ ADYACENCIA
	

	priority_queue<nodo> abiertos;
	float cota_superior = greedy(matriz_adyacencia);
	vector<int> recorrido;

	unsigned long nodos_analizados = 0, nodos_creados = 0, veces_poda = 0;


	for(int i = 1; i < tamanio; i++){
		nodo insertar(0, i, matriz_adyacencia[0][i], vminimo);
		abiertos.push(insertar);
		nodos_creados++;
	}
	
	auto tiempo = clock();
try{
	while(!abiertos.empty()){
		nodo aux = abiertos.top();
		abiertos.pop();
		nodos_analizados++;
		
		if(aux.getCota() < cota_superior){
			if(aux.solucion_parcial.size() == tamanio){
				float ultimo_paso = aux.getCota() + matriz_adyacencia[aux.solucion_parcial.back()][0] - vminimo[aux.solucion_parcial.back()];
				if(ultimo_paso < cota_superior){
					cota_superior = ultimo_paso;
					recorrido = aux.solucion_parcial;
					ultimo_paso = matriz_adyacencia[aux.solucion_parcial.back()][0];
					cout << "RECORRIDO: ";
					for(int i = 0; i < aux.solucion_parcial.size()-1;++i){
						ultimo_paso += matriz_adyacencia[aux.solucion_parcial[i]][aux.solucion_parcial[i+1]];
						cout << aux.solucion_parcial[i] << " ";
					}
					cout << aux.solucion_parcial.back() << " ";
					cout << "COSTE_TOTAL: "<< ultimo_paso << "\t\t";
					cout << "ANALIZADOS: " << nodos_analizados << "\t\tCREADOS: " << nodos_creados << "\t\tVECES PODA: " << veces_poda << "\t\tRESULTADO: " << cota_superior << endl;
				}
			}
			else{
				int analizando = aux.solucion_parcial.back();
				for(int i = 1; i < tamanio; i++){
					if(no_contiene(i, aux.solucion_parcial)){
						nodo insertar(aux);
						insertar.insertar_ciudad(i, matriz_adyacencia[analizando][i], vminimo);
						if(insertar.getCota() > cota_superior){
							veces_poda++;
						}
						else{
							abiertos.push(insertar);
							nodos_creados++;
						}
					}
				}
			}
		}
		else{
			cout << "FIN" << endl;
			break;
		}
	}
}
catch( const bad_alloc & e){
	cout << "NECESITO MAS RAM\n";
}
	
	tiempo = clock() - tiempo;

	cout << "\n...:::BRANCH & BOUND:::...\nRESULTADO: " << cota_superior << "\t\tTIEMPO: " << double(tiempo)/CLOCKS_PER_SEC << endl;
	cout << "ANALIZADOS: " << nodos_analizados << "\t\tCREADOS: " << nodos_creados << "\t\tVECES PODA: " << veces_poda << endl;
	for(int i = 0; i < recorrido.size();++i){
		cout << recorrido[i]+1 << endl;
	}
	// OPTIMO ulysses16 = 68.59
	//OPTIMO ulysses22 = 70.13
	
	return 0;
}
