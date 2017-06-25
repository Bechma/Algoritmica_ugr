#include <vector>
using namespace std;

class solucion{
	vector<pair<int,int>> resultado;
	int tamanio;
	int objetivo;
	bool terminado;
	
	void backtracking(vector<string> & problema, vector<pair<int,int>> & camino, int x, int y){
		if( x == objetivo and y == objetivo){
			resultado = camino;
			resultado.push_back(make_pair(x,y));
			terminado = true;
		}
		else{
			problema[x][y] = 'x';
			int destino;
		
			destino = x+1;
			if(destino < tamanio && problema[destino][y] == '0' && camino.back().first != destino && !terminado ){
				camino.push_back(make_pair(x,y));
				backtracking(problema, camino, destino, y);
				camino.pop_back();
			}
		
			destino = y+1;
			if(destino < tamanio && problema[x][destino] == '0' && camino.back().second != destino && !terminado ){
				camino.push_back(make_pair(x,y));
				backtracking(problema, camino, x, destino);
				camino.pop_back();
			}
		
			destino = x-1;
			if(destino >= 0 && problema[destino][y] == '0' && camino.back().first != destino && !terminado ){
				camino.push_back(make_pair(x,y));
				backtracking(problema, camino, destino, y);
				camino.pop_back();
			}
		
			destino = y-1;
			if(destino >= 0 && problema[x][destino] == '0' && camino.back().second != destino && !terminado ){
				camino.push_back(make_pair(x,y));
				backtracking(problema, camino, x, destino);
				camino.pop_back();
			}
		}
	}
	
	public:
	solucion(){}
	solucion(int n):tamanio(n){}
	
	int getTamanio(){return tamanio;}
	vector<pair<int,int>> getResultado(){return resultado;}
	
	void encontrarSalida(vector<string> & problema){
		vector<pair<int,int>> camino;
		
		terminado = false;
		objetivo = tamanio-1;
		resultado.clear();
		camino.push_back(make_pair(0,0));
		
		backtracking(problema, camino, 0, 1);
	}
};
