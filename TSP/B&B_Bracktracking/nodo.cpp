#include <vector>
using namespace std;

class nodo {
	float cota_inferior;

public:
	vector<int> solucion_parcial;
	nodo(){};
	nodo(int origen, int destino, float coste, const vector<float> & minimos) {
		solucion_parcial.push_back(origen);
		solucion_parcial.push_back(destino);
		cota_inferior = coste;
		for(int i = 1; i < minimos.size(); ++i)
			cota_inferior += minimos[i];
	}
	
	
	nodo(const nodo & c){*this=c;}
	~nodo(){}

	void insertar_ciudad(int x, const float & coste, const vector<float> & minimos){
		cota_inferior = cota_inferior + coste - minimos[solucion_parcial.back()];
		solucion_parcial.push_back(x);
	}

	float getCota() const{return cota_inferior;}


	nodo & operator=(const nodo & c){
		if(&c != this){
			solucion_parcial = c.solucion_parcial;
			cota_inferior = c.cota_inferior;
		}
		return *this;
	}

	bool operator<(const nodo & a) const{return cota_inferior > a.cota_inferior;}
};
