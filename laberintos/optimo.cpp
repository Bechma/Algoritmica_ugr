#include <vector>
using namespace std;

class optimo{
	vector<pair<int,int>> resultado;
	int tamanio;
	int objetivo;
	bool primera_vez;
	
	void backtracking(vector<string> & problema, vector<pair<int,int>> & camino, int x, int y){
		problema[x][y] = 'x';
		if( x == objetivo and y == objetivo and (primera_vez or resultado.size() > camino.size())){
			resultado = camino;
			resultado.push_back(make_pair(x,y));
			primera_vez = false;
		}
		else if( primera_vez or resultado.size() > camino.size() ){
			/* "debuger"
			for(int i = 0; i< problema.size(); i++)
				if( i == x)
					 cout << problema[i].substr(0,y) << "\033[1;31m" << problema[i][y] << "\033[0m" << problema[i].substr(y+1) << endl;
				else
					cout << problema[i] << endl;
			cout << endl;
			system("sleep 0.2");
			*/int destino;
		
			destino = x+1;
			if(destino < tamanio && problema[destino][y] == '0' && camino.back().first != destino ){
				camino.push_back(make_pair(x,y));
				backtracking(problema, camino, destino, y);
				camino.pop_back();
			}
		
			destino = y+1;
			if(destino < tamanio && problema[x][destino] == '0' && camino.back().second != destino ){
				camino.push_back(make_pair(x,y));
				backtracking(problema, camino, x, destino);
				camino.pop_back();
			}
		
			destino = x-1;
			if(destino >= 0 && problema[destino][y] == '0' && camino.back().first != destino ){
				camino.push_back(make_pair(x,y));
				backtracking(problema, camino, destino, y);
				camino.pop_back();
			}
		
			destino = y-1;
			if(destino >= 0 && problema[x][destino] == '0' && camino.back().second != destino ){
				camino.push_back(make_pair(x,y));
				backtracking(problema, camino, x, destino);
				camino.pop_back();
			}
			
		}
		problema[x][y] = '0';
	}
	
	public:
	optimo(){}
	optimo(int n):tamanio(n){}
	
	int getTamanio(){return tamanio;}
	vector<pair<int,int>> getResultado(){return resultado;}
	
	void encontrarSalida(vector<string> & problema){
		vector<pair<int,int>> camino;
		
		primera_vez = true;
		objetivo = tamanio-1;
		resultado.clear();
		camino.push_back(make_pair(0,0));
		
		backtracking(problema, camino, 0, 1);
	}
};
