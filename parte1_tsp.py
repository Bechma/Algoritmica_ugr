import math
import sys
from time import time

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
	Empieza primer algoritmo
	########################
"""

inicio = time()

mejor_resultado = sys.maxsize
mejor_solucion = list()

for x in range(len(matriz_adyacencia)):
	solucion = [x]

	for _ in range(1, len(matriz_adyacencia)):
		minimo = sys.maxsize
		proxima_ciudad = -1
		ciudad_actual = solucion[-1]
		for i in range(len(matriz_adyacencia)):
			if matriz_adyacencia[ciudad_actual][i] < minimo and i not in solucion:
				minimo = matriz_adyacencia[ciudad_actual][i]
				proxima_ciudad = i
		solucion.append(proxima_ciudad)

	coste_total = 0

	for i in range(len(solucion)):
		coste_total += matriz_adyacencia[solucion[i-1]][solucion[i]]

	if mejor_resultado > coste_total:
		mejor_resultado = coste_total
		mejor_solucion = solucion

transcurrido = time() - inicio

"""
	########################
	Termina primer algoritmo
	########################
"""

resultado = open(destino, 'w')

resultado.writelines("DIMENSION: " + str(len(mejor_solucion)) + "\n")
resultado.writelines([str(x+1)+"\n" for x in mejor_solucion])
resultado.writelines("\n" + str(mejor_resultado))


print("{0} {1} {2}".format(str(len(mejor_solucion)), str(transcurrido), str(mejor_resultado)))
