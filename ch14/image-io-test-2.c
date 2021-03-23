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
    if (img->pam.format == PPM_FORMAT || img->pam.format == RPPM_FORMAT){
        fprintf(stderr, "image is %dx%d, depth=%d, maxval=%d\n", img->pam.height, img->pam.width, img->pam.depth, (int)img->pam.maxval);
        img->pam.format = RPGM_FORMAT;
        img->pam.depth = 1;
        for (int i = 0; i < img->pam.height; i++) {
            for (int j = 0; j < img->pam.width; j++){
                double avg = (77 * img->r[i][j] + 150 * img->g[i][j] + 29 * img->b[i][j]) / 256.0;
                img->g[i][j] = (int)(0.5 + avg);
            }
        }
        write_image(argv[2], img);
        free_image(img);
        return EXIT_SUCCESS;
    }

    printf("Expected a ppm image in input\n");
    return EXIT_FAILURE;
}