#!/bin/bash
# Angel Asman
# x for col
# y for row
# This program takes a matrix and checks if the adjacent cells are infected by the zombie at the xy coord.

def checkAdj(population, x, y, strength):

    if (y < 0 or y > (len(population) -1)) or (x < 0 or x > (len(population[y]) -1)):
        return

    patientRes = population[y][x]

    #base case
    if patientRes == -1:
        return
    if population[y][x] <= strength:
        population[y][x] = -1
    #recurse
        checkAdj(population, x,y+1,strength)
        checkAdj(population, x+1,y,strength)
        checkAdj(population, x-1,y,strength)
        checkAdj(population, x,y-1,strength)
    
            
def answer(population, x, y, strength):

    popCopy = population[:]
    checkAdj(popCopy, x, y, strength)    
    print popCopy


pop = [[6,7,2,7,6],[6,3,1,4,7],[0,2,4,1,10],[8,1,1,4,9],[8,7,4,9,9]]

answer(pop,2,1,5)
