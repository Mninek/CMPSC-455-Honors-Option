#include <stdio.h>
#include "array.h"
#include "image-io.h"
#include "wavelet.h"
#include <math.h>

static int prune_matrix(double **a, int m, int n, double rel_err);
static void clip_matrix(double **a, int m, int n, int M);
static void reduce_pgm_image(struct image *img, double rel_err);
static void reduce_ppm_image(struct image *img, double rel_err);
void show_usage(char *progname);

static int prune_matrix(double **a, int m, int n, double rel_err) {
    float min = fabs(a[0][0]);
    float max = fabs(a[0][0]);
    //norm is the maximum of the column sums, norm2 is the square of the norm
    float norm2 = 0.0;
    int i, j;
    //cols
    for (j = 0; j < n; j++){
        //cols
        float colSum = 0.0;
        for (i = 0; i < m; i++){
            float curr = fabs(a[i][j]);
            colSum += curr;
            if (curr > max){
                max = curr;
            }
            if (curr < min){
                min = curr;
            }
            //compute norm2
            norm2 = norm2 + (curr * curr);
        }
    }
    //compute abs_err2
    float abs_err2 = norm2 * (rel_err * rel_err);

    //calculate cutoff var
    float t = (min+max) / 2;

    //stopping criteria
    while (max - min >= ( 0.000001 * (sqrt(norm2)))){
        t = (min+max) / 2;
        float sum = 0.0;
        //we are going to iterate over the matrix and sum the squares of each value that is less than or equal to t.
        for (i = 0; i < m; i++){
            for (j = 0; j < n; j++){
                float curr = fabs(a[i][j]);
                if (curr <= t){
                    sum += (curr*curr);
                }
            }
        }

        //check book's case 2
        if (sum > abs_err2){
            max = t;
        }
        else if (sum < abs_err2){
            min = t;
        }
    }

    //now we zero some entries and keep track of the count of zeroed entries
    int zeroes = 0;
    for (i = 0; i < m; i++){ 
        for (j = 0; j < n; j++){
            //if entry is less than t we zero it
            if (fabs(a[i][j]) < t){
                a[i][j] = 0;
                zeroes++;
            }
        }
    }
    return zeroes;
}

static void clip_matrix(double **a, int m, int n, int M) {
    int i, j;
    for (i = 0; i < m; i++){ 
        for (j = 0; j < n; j++){
            //if entry is less than t we zero it
            if (a[i][j] < 0){
                a[i][j] = 0;
            } 
            //if entry greater than M we just set to M
            else if (a[i][j] > M){
                a[i][j] = M;
            } 
            //else round to the nearest int
            else {
                a[i][j] = (int)(a[i][j] + 0.5);
            }
        }
    }
}

static void reduce_pgm_image(struct image *img, double rel_err) {
    int m = img->pam.height;
    int n = img->pam.width;
    int M = img->pam.maxval;
    int zero_count;
    haar_transform_matrix(img->g, m, n, WT_FWD);
    zero_count = prune_matrix(img->g, m, n, rel_err);
    haar_transform_matrix(img->g, m, n, WT_REV);
    clip_matrix(img->g, m, n, M);
    fprintf(stderr, "zeroed %d of %d wavelet coefficients, %d remaining\n",
    zero_count, m*n, m*n - zero_count);
}

static void reduce_ppm_image(struct image *img, double rel_err) {
    int m = img->pam.height;
    int n = img->pam.width;
    int M = img->pam.maxval;
    int zero_count;
    //same process as in the book except we need to apply it to the r, g, b components
    haar_transform_matrix(img->g, m, n, WT_FWD);
    haar_transform_matrix(img->r, m, n, WT_FWD);
    haar_transform_matrix(img->b, m, n, WT_FWD);
    double **t;
    make_matrix(t, m, n);
    //initialize the t
    int i, j;
    for (i = 0; i < m; i++){ 
        for (j = 0; j < n; j++){
            t[i][j] = sqrt((1.0/3.0) * ((img->r[i][j] * img->r[i][j]) + (img->g[i][j] * img->g[i][j]) + (img->b[i][j] * img->b[i][j])));
        }
    }
    zero_count = prune_matrix(t, m, n, rel_err);
    for (i = 0; i < m; i++){ 
        for (j = 0; j < n; j++){
            //if the t got dropped, all elements of r g b get dropped as well
            if(t[i][j] == 0){
                img->r[i][j] = 0;
                img->g[i][j] = 0;
                img->b[i][j] = 0;
            }
        }
    }
    haar_transform_matrix(img->g, m, n, WT_REV);
    haar_transform_matrix(img->b, m, n, WT_REV);
    haar_transform_matrix(img->r, m, n, WT_REV);
    clip_matrix(img->g, m, n, M);
    clip_matrix(img->b, m, n, M);
    clip_matrix(img->r, m, n, M);
    fprintf(stderr, "zeroed %d of %d wavelet coefficients, %d remaining\n",
    zero_count, m*n, m*n - zero_count);
}

void show_usage(char *progname){
    printf("Usage: ./image-analysis rel_err infile outfile\n 0.0 <= rel_err <= 1.0\n1. Reads a PGM or PPM image from infile\n");
    printf("2. Applies the Haar wavelet transform\n3. Sets as many of the smallest wavelet coefficients to zero\nas possible while keeping the relative error\n");
    printf("(in the L^2 norm) just under rel_err\n4. Reconstructs image with the truncated coefficients and\nwrites to outfile\n");
}

int main(int argc, char **argv) {
    char *infile, *outfile, *endptr;
    double rel_err;

    if (argc != 4) {
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }

    rel_err = strtod(argv[1], &endptr);
    if (*endptr != '\0' || rel_err < 0.0 || rel_err > 1.0) {
        fprintf(stderr, "*** the rel_err argument should be between 0.0 and 1.0\n");
        return EXIT_FAILURE;
    }

    infile = argv[2];
    outfile = argv[3];
    pm_init(argv[0], 0);
    struct image *img = read_image(infile);
    struct pam *pam = &img->pam;
    if (pam->format == PGM_FORMAT || pam->format == RPGM_FORMAT)
        reduce_pgm_image(img, rel_err);
    else if (pam->format == PPM_FORMAT || pam->format == RPPM_FORMAT)
        reduce_ppm_image(img, rel_err);
    else {
        fprintf(stderr, "*** file %s, line %d: shouldn't be here\n",__FILE__, __LINE__);
        return EXIT_FAILURE;
    }

    write_image(outfile, img);
    free_image(img);
    return EXIT_SUCCESS;
}