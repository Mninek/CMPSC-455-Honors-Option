#include <stdio.h>
#include "write.h"
#include "linked-list.h"
static void print_animal(struct animal *animal);
static void print_herd(conscell *herd);
int write_wdf(struct world *world);

static void print_animal(struct animal *animal){
    if (animal->i > 9 || animal->j > 9){
        printf("( %d, %d)\t%d\t%d\t| %d    %d    %d    %d    %d    %d    %d    %d |\n", animal->i, animal->j, animal->d, animal->e, animal->genes[0], 
                                                                                    animal->genes[1], animal->genes[2], animal->genes[3], animal->genes[4], animal->genes[5],
                                                                                    animal->genes[6], animal->genes[7]);
    } else {
        printf("( %d, %d)\t\t%d\t%d\t| %d    %d    %d    %d    %d    %d    %d    %d |\n", animal->i, animal->j, animal->d, animal->e, animal->genes[0], 
                                                                                    animal->genes[1], animal->genes[2], animal->genes[3], animal->genes[4], animal->genes[5],
                                                                                    animal->genes[6], animal->genes[7]);
    }
}

static void print_herd(conscell *herd){
    int count = 0;
    while(herd){
        print_animal(herd->data);
        herd = herd->next;
        count ++;
    }
    printf("# animal count: %d\n", count);
    return;
}

int write_wdf(struct world *world){
    printf("World %d %d\nEden %d %d\nPlant Energy %d\nReproduction Threshold %d\n\n #( i j)\td\te\t| g[0] g[1] g[2] g[3] g[4] g[5] g[6] g[7]|\n", \
                                                                                             world->world_h, world->world_w, world->eden_h, world->eden_w, \
                                                                                            world->plant_energy, world->reproduction_threshold);
    printf("#-------------------------------|--------------------------------------|\n");
    print_herd(world->herd);
    return 0;
}