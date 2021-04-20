#ifndef H_EVOLUTION_H
#define H_EVOLUTION_H
#include "linked-list.h"
struct animal {
    int i; // row number of animal’s position
    int j; // column number of animal’s position
    int d; // direction the animal is facing: 0,...,7
    int e; // animal’s energy
    int genes[8]; // the animal’s chromosome (array of genes)
} animal;
struct world {
    int world_h; // world’s height
    int world_w; // world’s width
    int eden_h; // Eden’s height
    int eden_w; // Eden’s width
    int plant_energy; // plant energy
    int reproduction_threshold; // reproduction threshold
    int **plants; // world_h × world_w array of plants
    conscell *herd; // the head of the linked list of the animals
};
#endif /* H_EVOLUTION_H */