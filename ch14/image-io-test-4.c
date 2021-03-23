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
        for (int i = 0; i < img->pam.height; i++) {
            for (int j = 0; j < img->pam.width; j++){
                int red = img->r[i][j];
                int green = img->g[i][j];
                int blue = img->b[i][j];
                img->r[i][j] = blue;
                img->g[i][j] = red;
                img->b[i][j] = green;
            }
        }
        write_image(argv[2], img);
        free_image(img);
        return EXIT_SUCCESS;
    }

    printf("Expected a ppm image in input\n");
    return EXIT_FAILURE;
}