#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <set>
using namespace std;



typedef vector<vector<int> > laberinto;


/**
   @brief Sobrecarga del operador '<<' para laberinto.

   @param s: flujo de salida.
   @param lab: laberinto.
   @return s, el flujo de salida recibido.
*/
ostream & operator<< (ostream & s, const laberinto & lab)
{
  
//s << "laberinto (" << lab.size() <<")" << endl;
for (int i=0; i<lab.size(); i++){
   for (int j=0; j<lab.size();j++) 
      if (lab[i][j]==-1)  s << '-'; 
      else  s << lab[i][j];
   s << endl;
}
s << endl;
return s;
}


bool valida(pair<int,int> & celda, int tama){
  if ((celda.first <=0) || (celda.first >= tama-1) ) return false;
  if ((celda.second <=0) || (celda.second >= tama-1) ) return false;
  return true;
}

bool cicloGenerado(pair<int,int> & celda, pair<int,int> & ant, set<pair<int,int> > & generado)
{
  pair<int,int> aux(celda);
  aux.first = celda.first -1; 
  if ( (aux != ant) &&  (generado.find(aux) != generado.end()))  return true;
  
  aux.first = celda.first +1;
  if ( (aux != ant) &&  (generado.find(aux) != generado.end()))  return true;  
 
  aux = celda;
   aux.second = celda.second -1;
  if ( (aux != ant) &&  (generado.find(aux) != generado.end()))  return true;  
  aux.second = celda.second +1;
  if ( (aux != ant) &&  (generado.find(aux) != generado.end()))  return true;  
  return false;
}
pair<int,int> pos_aleatoria(set<pair<int,int> > & generado){
 
  int x = rand() % generado.size();
  int i;
  set<pair<int,int> >::iterator it;
  for (it = generado.begin(), i=0; i< x; i++,it++);
  return *it;
}
/* 
*/
void Genera_laberinto(int tama, int n_ramas, laberinto & lab){
   
vector<int> fila(tama,-1);
lab.resize(tama,fila);
int xy,cont_mov,ramas;
bool avanza;
pair<int,int> celda,ant,act;
set<pair<int,int> >generado;
bool ciclo;
srand ( time(NULL) );

celda.first = 0;
celda.second = 1;
generado.insert(celda);

celda.first = 1;
generado.insert(celda);
  /* genero camino inicial */
lab[0][1] = 0; lab[1][1] = 0;
ant = celda;
ramas = 0;
      
 
do {
  cont_mov = 0;
  avanza = false;
  xy = rand()%4;  // 0=^, 1 = >, 2 = v, 3 = <
  act=celda = ant;
  do {
    celda = act;
    if (xy == 0) celda.second--;
    else if (xy == 1) celda.first++;
    else if (xy == 2) celda.second++;
    else celda.first--;
    cont_mov++;
    if ( (valida(celda,tama) && !cicloGenerado(celda, ant,generado) ) ) {
      avanza = true;
      lab[celda.first][celda.second] = 0;
      generado.insert(celda);
      ant = celda;
    } else xy=(xy+1)%4;
  } while ( (cont_mov < 5) && !avanza);
  
  if (cont_mov == 5) { // estamos en un punto sin salida, cogemos un punto al azar del recorrido para seguir
    ant = pos_aleatoria(generado);
    ramas++;
  }
} while (ramas<n_ramas);
 

celda = *(generado.rbegin());

while (celda.first < tama-2){
  
  celda.first++;
  lab[celda.first][celda.second] = 0;
}
while (celda.second<tama-1) {
  celda.second++;
  lab[celda.first][celda.second] = 0;
}
celda.first = tama-1;
celda.second = tama-1;
lab[celda.first][celda.second] = 0;
 
      
 }

 
   
//////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
  
  map<int, pair<double, double> >  M;
  if (argc != 3) {
     cout << "Error Formato: nombre_ejecutable tamanio ramas" << endl;
     exit(1);
   }
   
  
    
int tama = atoi(argv[1]),ramas = atoi(argv[2]);
laberinto x;

Genera_laberinto(tama, ramas, x);
cout << tama << endl;
cout << x;
 
    return 0;
}
