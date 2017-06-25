//
// COMPILAR CON g++ -std=c++11 -Ofast -o ejecutable backtracking.cpp
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

float cota_superior;
vector<float> vminimo;
vector<int> recorrido;
unsigned long nodos_creados = 0, veces_poda = 0;

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





void backtracking(const vector<vector<float>> & matriz, float cota_inferior, vector<int> & sol_parcial){
	nodos_creados++;
	if(sol_parcial.size() == matriz.size()){
		float ultimo_paso = cota_inferior + matriz[sol_parcial.back()][0] - vminimo[sol_parcial.back()];
		if(ultimo_paso <= cota_superior){
			cota_superior = ultimo_paso;
			recorrido = sol_parcial;
			cout << "CREADOS: " << nodos_creados << "\t\tVECES PODA: " << veces_poda << "\t\tRESULTADO: " << cota_superior << endl;
		}
	}
	else{
		int analizando = sol_parcial.back();
		for(int i = 1; i < matriz.size(); i++){
			if(no_contiene(i, sol_parcial)){
				float nueva_cota = cota_inferior + matriz[analizando][i] - vminimo[analizando];
				if(nueva_cota > cota_superior){
					veces_poda++;
				}
				else{
					sol_parcial.push_back(i);
					backtracking(matriz, nueva_cota, sol_parcial);
					sol_parcial.pop_back();
				}
			}
		}
	}
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
	

	cota_superior = greedy(matriz_adyacencia);
	float cota_inicial = 0;
	
	for(int i = 0; i < vminimo.size(); i++)
		cota_inicial += vminimo[i];

	
	auto tiempo = clock();
	
try{
	vector<int> ini;
	ini.push_back(0);
	backtracking(matriz_adyacencia, cota_inicial, ini);
}
catch( const bad_alloc & e){
	cout << "NECESITO MAS RAM\n";
}
	
	tiempo = clock() - tiempo;

	cout << "\n...:::BACKTRACKING:::...\nRESULTADO: " << cota_superior << "\t\tTIEMPO: " << double(tiempo)/CLOCKS_PER_SEC << endl;
	cout << "CREADOS: " << nodos_creados << "\t\tVECES PODA: " << veces_poda << endl;
	for(int i = 0; i < recorrido.size();++i){
		cout << recorrido[i]+1 << endl;
	}
	// OPTIMO ulysses16 = 68.59
	//OPTIMO ulysses22 = 70.13
	
	return 0;
}
