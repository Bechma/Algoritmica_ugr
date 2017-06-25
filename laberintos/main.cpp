#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include "solucion.cpp"
#include "optimo.cpp"
using namespace std;

int main (int argc, char *argv[]){
	if(argc != 2){
		cout << argv[1] << " archivo_laberinto" << endl;
		return 1;
	}
	
	vector<string> laberinto;
	
	
	fstream f(argv[1]);
	string s;
	getline(f, s);
	int tamanio = stoi(s);
	
	for(int i = 0; i < tamanio;i++){
		getline(f, s);
		laberinto.push_back(s);
	}
	
	vector<string> laberintoO(laberinto);
	
	optimo solO(tamanio);
	solucion sol(tamanio);
	
	chrono::steady_clock::time_point inicio = std::chrono::steady_clock::now();
	sol.encontrarSalida(laberinto);
	chrono::steady_clock::time_point fin = std::chrono::steady_clock::now();
	
	chrono::steady_clock::time_point inicioO = std::chrono::steady_clock::now();
	solO.encontrarSalida(laberintoO);
	chrono::steady_clock::time_point finO = std::chrono::steady_clock::now();
	
	
	double tiempo = chrono::duration_cast<std::chrono::nanoseconds> (fin - inicio).count();
	double tiempoO = chrono::duration_cast<std::chrono::nanoseconds> (finO - inicioO).count();
	
	tiempo /= 1e9;
	tiempoO /= 1e9;
	
	
	for(auto & i : solO.getResultado())
		if( (i.first == 0 and i.second == 0) or (laberintoO[i.first][i.second] == '0' or laberintoO[i.first][i.second] == 'x'))
			laberintoO[i.first][i.second] = '1';
		else{
			cout << "ERROR   " << i.first << " " << i.second << endl;
		}
	for(auto & i : sol.getResultado())
		if( (i.first == 0 and i.second == 0) or (laberinto[i.first][i.second] == '0' or laberinto[i.first][i.second] == 'x'))
			laberinto[i.first][i.second] = '1';
		else{
			cout << "ERROR   " << i.first << " " << i.second << endl;
		}
	cout << tamanio << " " << tiempo << endl;
	cerr << tamanio << " " << tiempoO << endl;
	
//	for(int i = 0; i < laberinto.size(); i++)
//		cout << laberinto[i] << endl;
//	
//	for(int i = 0; i < laberinto.size(); i++)
//		cout << laberintoO[i] << endl;
//	
//	cout << endl << endl;
	
	
}
