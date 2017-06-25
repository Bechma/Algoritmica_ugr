import math
import sys
from time import time


def calcular_camino(sol):
	"""
		Funcion para calcular el camino que haya hasta el momento
	"""
	coste = 0
	for k in range(len(sol)):
		coste += matriz_adyacencia[sol[k-1]][sol[k]]
	return coste


def hay_ciclo(grafo, nodo_insertar):
	"""
		Funcion para calcular si un grafo sin ciclos consigue un ciclo al insertarle un nodo
	"""
	copia = grafo.copy()
	copia[nodo_insertar[0]] = nodo_insertar[1]
	actual = nodo_insertar[0]
	while True:
		encontrado = False
		if actual in copia:
			actual = copia[actual]
			encontrado = True

		if not encontrado:
			return False
		elif actual == nodo_insertar[0]:
			return True

"""
	########################
	Inicio cogida de datos
	########################
"""

try:
	basura, tsp, destino = sys.argv
except:
	print("ERROR argumentos: <ejecutable> + <fichero_con_tsp> + <fichero_datos_destino>")
	raise SystemExit

archivo = open(tsp, 'r').read().splitlines()[1:]

numeros = list()

for i in archivo:
	numeros.append([float(j) for j in i.split()])

matriz_adyacencia = list()

while True:
	try:
		numeros.remove([])
	except ValueError:
		break

for i in numeros:
	matriz_adyacencia.append([math.sqrt(math.pow(i[1]-x[1], 2)+math.pow(i[2]-x[2], 2)) for x in numeros])

if len(matriz_adyacencia) < 3:
	print("Problema con menos de 3 nodos, abortando.")
	raise SystemExit

"""
	########################
	FIN cogida de datos
	########################
"""


inicio = time()
"""
	########################
	Empieza tercer algoritmo
	########################
"""
aristas = []

# Crear aristas a partir de matriz de adyacencia
for i in range(len(matriz_adyacencia)):
	for j in range(0, len(matriz_adyacencia)):
		if matriz_adyacencia[i][j] != 0:
			aristas.append((i, j, matriz_adyacencia[i][j]))

# Ordeno las aristas por menor distancia
aristas.sort(key=lambda x: x[2])

# Llevo la cuenta del numero de aristas de cada nodo
analizados = [0 for i in range(len(matriz_adyacencia))]

# Se permitira que haya un ciclo, solo si todos los nodos tienen 2 aristas asociadas excepto 2 nodos
SE_PERMITE_CICLO = (len(matriz_adyacencia)-2) * 2 + 2
contador_vertices_conectados = 0

sol_parcial = dict()

for i in aristas:
	# Si nodo origen [0] ya ha sido seleccionado como [0], se descarta la arista
	# Y si el nodo destino [1] ya ha sido seleccionado como [1], se descarta la arista
	if i[0] not in sol_parcial and i[1] not in sol_parcial.values():
		# Si los nodos de la arista no han sido unidos por otra arista, significa que es una componente conexa
		# y que no tiene ciclos. Si hubiese un nodo que ya estaba conectado y otro que no ha sido conectado,
		# es imposible que haga ciclo, por lo tanto no se comprueba.
		if (analizados[i[0]] == 0 and analizados[i[1]] == 0) or \
				(analizados[i[0]] == 1 and analizados[i[1]] == 0) or \
				(analizados[i[0]] == 0 and analizados[i[1]] == 1):
			analizados[i[0]] += 1
			analizados[i[1]] += 1
			contador_vertices_conectados += 2
			sol_parcial[i[0]] = i[1]
		# Si los nodos de la arista han sido unidos ambos, por otras aristas, entonces hay que comprobar si
		# se esta formando un ciclo. Excepto si solo queda por unir dos vertices, que entonces se va a formar el camino
		# que estamos buscando.
		elif (contador_vertices_conectados == SE_PERMITE_CICLO or not hay_ciclo(sol_parcial, i)):
			analizados[i[0]] += 1
			analizados[i[1]] += 1
			contador_vertices_conectados += 2
			sol_parcial[i[0]] = i[1]
			# Si ya hemos unido los dos ultimos nodo que quedaba por unir, dejo de analizar aristas
			if contador_vertices_conectados == SE_PERMITE_CICLO+2:
				break

solucion = [0]
analizando = 0
iteraciones = len(sol_parcial)-1
for i in range(iteraciones):
	solucion.append(sol_parcial[analizando])     # añado la ciudad a la solucion
	analizando = sol_parcial[analizando]         # me quedo con la siguiente ciudad

transcurrido = time() - inicio

"""
	########################
	Termina tercer algoritmo
	########################
"""

"""
	Poner resultados en archivo destino y pantalla
"""

resultado = open(destino, 'w')

coste_camino = calcular_camino(solucion)

resultado.writelines("DIMENSION: " + str(len(solucion)) + "\n")
resultado.writelines([str(x+1) + " " + str(numeros[x][1]) + " " + str(numeros[x][2]) + "\n" for x in solucion])
resultado.writelines("\n" + str(coste_camino))

# Para una salida con "nºnodos tiempo"
print("{0} {1} {2}".format(str(len(solucion)), str(transcurrido), str(coste_camino)))
