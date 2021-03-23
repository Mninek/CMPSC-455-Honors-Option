#include <stdio.h>
#include "image-io.h"
int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        fprintf(stderr, "Reads PGM or PPM from infile, writes identical image to outfile\n");
        return EXIT_FAILURE;
    }
    pm_init(argv[0], 0);
    struct image *img = read_image(argv[1]);
    fprintf(stderr, "image is %dx%d, depth=%d, maxval=%d\n", img->pam.height, img->pam.width, img->pam.depth, (int)img->pam.maxval);
    
    for (int i = 0; i < img->pam.height; i++) {
        //this does the left to right forward diagonal
        img->r[i][(int) (0.5 + (((double)i * (img->pam.width - 1))/(img->pam.height - 1)))] = 0;
        img->g[i][(int) (0.5 + (((double)i * (img->pam.width - 1))/(img->pam.height - 1)))] = 0;
        img->b[i][(int) (0.5 + (((double)i * (img->pam.width - 1))/(img->pam.height - 1)))] = 0;

        //this does the right to left backwards diagonal
        img->r[i][(int) (0.5 + (((double)(img->pam.height - i) * (img->pam.width - 1))/(img->pam.height - 1)))] = 0;
        img->g[i][(int) (0.5 + (((double)(img->pam.height - i) * (img->pam.width - 1))/(img->pam.height - 1)))] = 0;
        img->b[i][(int) (0.5 + (((double)(img->pam.height - i) * (img->pam.width - 1))/(img->pam.height - 1)))] = 0;
    }
    write_image(argv[2], img);
    free_image(img);
    return EXIT_SUCCESS;
}