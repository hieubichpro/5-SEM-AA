import numpy as np
from random import random

from in_out import read_matrix, getCoefs, print_matrix
import itertools as it

MIN_PHEROMONE = 0.01


def getQ(matrix, size):
    q = 0
    count = 0

    for i in range(size):
        for j in range(size):
            if i != j:
                q += matrix[i][j]
                count += 1

    return q / count


def getPheromone(size):
    pheromone = [[1 for i in range(size)] 
                        for j in range(size)]

    return pheromone


def getVisibility(matrix, size):
    visibility = [[(1.0 / matrix[i][j] if (i != j) else 0) 
                        for j in range(size)] 
                            for i in range(size)]

    return visibility


def getVisitedCity(route, ants):
    visited = [[] for _ in range(ants)]

    for i in range(ants):
        visited[i].append(route[i])

    return visited


def update_pheromone(matrix, size, visited, pheromone, q, evaporation):
    ants = size

    for i in range(size):
        for j in range(size):
            delta = 0

            for ant in range(ants):
                length = getDistance(matrix, size, visited[ant])
                delta += q / length

            pheromone[i][j] *= (1 - evaporation)
            pheromone[i][j] += delta

            if pheromone[i][j] < MIN_PHEROMONE:
               pheromone[i][j] = MIN_PHEROMONE

    return pheromone


def getNextCity(pk):
    size = len(pk)
    numb = 0
    i = 0

    probability = random()

    while numb < probability and i < size:
        numb += pk[i]
        i += 1

    return i


def searchProbability(pheromone, visibility, visited, size, ant, alpha, beta):
    pk = [0] * size

    for i in range(size):
        if i not in visited[ant]:
            ant_i = visited[ant][-1]

            pk[i] = pow(pheromone[ant_i][i], alpha) * \
                    pow(visibility[ant_i][i], beta)
        else:
            pk[i] = 0

    pk_sum = sum(pk)

    for i in range(size):
        pk[i] /= pk_sum  

    return pk


def antAlgo(matrix, size, alpha, beta, evaporation, days):
    pheromone = getPheromone(size)
    visibility = getVisibility(matrix, size)

    Q = getQ(matrix, size)

    res = []
    minSofar = float("inf")

    for _ in range(days):
        visited = getVisitedCity(np.arange(size), size)
        for i in range(size):
            while len(visited[i]) != size:
                pk = searchProbability(pheromone, visibility, visited, size, i, alpha, beta)  
                nextCity = getNextCity(pk)

                visited[i].append(nextCity - 1)

            visited[i].append(visited[i][0])
            
            currLen = getDistance(matrix, size, visited[i]) 

            if currLen < minSofar:
                minSofar = currLen
                res = visited[i]

        pheromone = update_pheromone(matrix, size, visited, pheromone, Q, evaporation)

    return minSofar, res


def solveAntAlgo():
    matrix = read_matrix()
    size = len(matrix)
    print_matrix(matrix)
    alpha, beta, evaporation, days = getCoefs()
    minSofar, res = antAlgo(matrix, size, alpha, beta, evaporation, days)

    print("\nМинимальная сумма пути: ", minSofar,
          "\nМинимальный путь: ", res)
    
def getDistance(matrix, size, way):
    length = 0

    for i in range(size):
        beg_city = way[i]
        end_city = way[i + 1]

        length += matrix[beg_city][end_city]

    return length


def bruteForce(matrix, n):
    cities = np.arange(n)
    variants = []

    for comb in it.permutations(cities):
        variants.append(list(comb))

    res = []
    minSoFar = float("inf")

    for i in range(len(variants)):
        variants[i].append(variants[i][0])

        length = getDistance(matrix, n, variants[i])

        if length < minSoFar:
            minSoFar = length
            res = variants[i]

    return minSoFar, res


def solveBruteForce():
    matrix = read_matrix()
    print_matrix(matrix)
    size = len(matrix)

    minSofar, res = bruteForce(matrix, size)

    print("\nМинимальная сумма пути:", minSofar, "\nМинимальный путь: ", res)

    