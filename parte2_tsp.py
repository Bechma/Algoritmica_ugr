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

"""
	########################
	Empieza segundo algoritmo
	########################
"""

inicio = time()
solucion = [0, len(matriz_adyacencia)//2, len(matriz_adyacencia)-1]

for i in range(len(matriz_adyacencia)):
	if i not in solucion:
		minimo = sys.maxsize
		posicion = 1
		ciudad = 1
		for j in range(len(solucion)):
			aux = solucion[:]
			aux.insert(j, i)
			coste_camino = calcular_camino(aux)
			if coste_camino < minimo:
				minimo = coste_camino
				ciudad = i
				posicion = j
		solucion.insert(posicion, ciudad)

transcurrido = time() - inicio

"""
	########################
	Termina segundo algoritmo
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
