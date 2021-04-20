#include <stdio.h>
#include "array.h"
#include "read.h"
#include "write.h"
#include "xmalloc.h"
#include "evolution.h"

int main(int argc, char **argv) {
    struct world *world = (struct world *)xmalloc(sizeof(struct world));
    read_wdf(world);
    write_wdf(world);
    return 0;
}