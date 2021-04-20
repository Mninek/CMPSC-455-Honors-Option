#include <stdio.h>
#include "evolution.h"
#include "xmalloc.h"
#include "array.h"
#include "read.h"
#include "write.h"
#include "linked-list.h"
#include "world-to-eps.h"
#define MAX(a,b) ((a) > (b) ? (a) : (b))
struct point_evo {
    int i;
    int j;
};
static inline int random(int n);
static void free_herd(conscell *herd);
static int dead_or_alive(const void *aa);
static conscell *remove_the_dead(conscell *herd);
static int nearer_the_eden(const void *aa, const void *bb, void *params);
static void initialize_plants(struct world *world);
static void add_plants(struct world *world);
static int gene_to_activate(int genes[8]);
static void turn(struct animal *animal);
static void move(struct world *world, struct animal *animal);
static void feed(struct world *world, struct animal *animal);
static struct animal *clone(struct animal *old);
static void mutate(int genes[8]);
static void reproduce(struct world *world, struct animal *animal);
static void update_world(struct world *world);
static void evolve(struct world *world, unsigned int n);
static void evolve_with_figs(struct world *world, unsigned int n);
static void show_usage(char *progname);

int main(int argc, char **argv)
{
    unsigned long int n; // number of updates
    unsigned long int f = 0; // number of figures to generate
    struct world World;
    struct world *world = &World;
    int exit_status = EXIT_FAILURE;
    world->herd = NULL;
    world->plants = NULL;
    if (argc < 2 || argc > 3) {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (sscanf(argv[1], "%lu", &n) != 1) {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (argc > 2 && sscanf(argv[2], "%lu", &f) != 1) {
        show_usage(argv[0]);
        goto cleanup;
    }

    if (!read_wdf(world)) {
        printf("failed to read the wdf\n");
        goto cleanup;
    }

    initialize_plants(world);
    evolve(world, n);
    if (f > 0)
        evolve_with_figs(world, f);

    struct point_evo eden_center;
    eden_center.i = (world->world_h - 1)/2;
    eden_center.j = (world->world_w - 1)/2;
    world->herd = ll_sort(world->herd, nearer_the_eden, &eden_center);
    write_wdf(world);
    exit_status = EXIT_SUCCESS;

cleanup:
    free_matrix(world->plants);
    free_herd(world->herd);
    return exit_status;
}

static void show_usage(char *progname){
    printf("\nUsage: ./%s n [f] <infile >outfile\n", progname);
    printf("n >= 0 : (required) number of updates\n");
    printf("f >= 0 : (optional) number of snapshots after n updates\n");
    printf("Reads World Definition from infile, performs\n n updates, and writes result to outfile\n");
}

static inline int random(int n){
    return rand()/(RAND_MAX/n + 1);
}

static void free_herd(conscell *herd){
    for (conscell *p = herd; p != NULL; p = p->next)
        free(p->data);
    ll_free(herd);
}

static int dead_or_alive(const void *aa){
    struct animal *a=(struct animal *)aa;
    if(a->e <= 0){
        return 1;
    }
    return 0;
}

static conscell *remove_the_dead(conscell *herd){
    conscell *dead = NULL;
    herd = ll_filter(herd, dead_or_alive, &dead);
    free_herd(dead);
    return herd;
}

int phi(int x, int L)
{
    int d = abs(x);
    if (d > L/2)
    d = L - d;
    return d;
}

//needs to be modified for off-center edens
static int nearer_the_eden(const void *aa, const void *bb, void *params){
    struct point_evo *a=(struct point_evo *)aa;
    struct point_evo *b=(struct point_evo *)bb;
    struct point_evo *p=(struct point_evo *)params;
    int d1,d2;
    d1 = MAX(a->i - p->i, a->j - p->j);
    d2 = MAX(b->i - p->i, b->j - p->j);
    if (d1 < d2)
        return -1;
    else if (d1 > d2)
        return 1;
    else
        return 0;
}

static void initialize_plants(struct world *world){
    make_matrix(world->plants, world->world_h, world->world_w);
    int i, j;
    for (i = 0; i < world->world_h; i++){
        for (j = 0; j < world->world_w; j++){
            world->plants[i][j] = 0;
        }
    }
}

static void add_plants(struct world *world)
{
    int i = random(world->world_h);
    int j = random(world->world_w);
    world->plants[i][j]++;

    if (world->eden_h > 0 && world->eden_w > 0) {
        i = random(world->eden_h);
        j = random(world->eden_w);
        world->plants[i][j]++;
    }
}

static int gene_to_activate(int genes[8]){
    int i;
    int L = 0;
    //get the line segment
    for (i = 0; i < 8; i++){
        L += genes[i];
    }

    //generate r in this range
    int r = random(L);

    //go through all the genes again, but decrement r by the value so we can return the correct gene.
    for (i = 0; i < 8; i++){
        r -= genes[i];
        if (r <= 0){
            return i;
        }
    }
    return -1; //error
}

static void turn(struct animal *animal){
    int k = gene_to_activate(animal->genes);
    animal->d = (animal->d + k) % 8;
}

static void move(struct world *world, struct animal *animal)
{
    struct {
        int i;
        int j;
    } motion_vectors[] = {
        { 1 , 0 },
        { 1 , 1 },
        { 0 , 1 },
        {-1 , 1 },
        {-1 , 0 },
        {-1 , -1 },
        { 0 , -1 },
        { 1 , -1 }};
    int i = animal->i + motion_vectors[animal->d].i;
    int j = animal->j + motion_vectors[animal->d].j;
    if (i < 0)
        i += world->world_h;
    else if (i >= world->world_h)
        i -= world->world_h;
    if (j < 0)
        j += world->world_w;
    else if (j >= world->world_w)
        j -= world->world_w;
    animal->i = i;
    animal->j = j;
}

static void feed(struct world *world, struct animal *animal){
    int i = animal->i;
    int j = animal->j;
    if (world->plants[i][j] > 0){
        world->plants[i][j] -=1;
        animal->e += world->plant_energy;
    }
}

static struct animal *clone(struct animal *old){
    struct animal *new = xmalloc(sizeof *new);
    new->i = old->i;
    new->j = old->j;
    new->d = old->d;
    new->e = old->e;
    int i = 0;
    for (; i < 8; i++){
        new->genes[i] = old->genes[i];
    }
    return new;
} 
static void mutate(int genes[8]){
    int gene = random(8);
    int mutation = random(3) - 1;
    genes[gene] += mutation;
    if (genes[gene] < 1){
        genes[gene] = 1;
    }
}

static void reproduce(struct world *world, struct animal *animal)
{
    animal->e /= 2;
    struct animal *new = clone(animal);
    mutate(new->genes);
    world->herd = ll_push(world->herd, new);
}

static void update_world(struct world *world)
{
    world->herd = remove_the_dead(world->herd);
    for (conscell *p = world->herd; p != NULL; p = p->next) {
        struct animal *a=p->data;
        turn(a);
        move(world, a);
        feed(world, a);
        a->e--;
        if (a->e >= world->reproduction_threshold)
            reproduce(world, a);
    }
    add_plants(world);
}

static void evolve(struct world *world, unsigned int n){
    int i;
    for (i = 0; i < n; i++){
        update_world(world);
        if (i % 100000 == 0){
            printf("iteration %d\n", i);
        }
    }
}

static void evolve_with_figs(struct world *world, unsigned int n){
    char buf[16]; // an overkill – only 12 chars are needed
    for (unsigned long int i = 0; i < n; i++) {
        sprintf(buf, "fig%04lu.eps", i);
        world_to_eps(world, buf);
        if (i < n - 1)
            update_world(world);
    }
}