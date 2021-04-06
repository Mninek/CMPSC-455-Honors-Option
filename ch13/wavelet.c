#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wavelet.h"
#include "array.h"
#define SQRT1_2 sqrt(1.0/2)
static void haar_transform_vector_forward(double *v, int n);
static void haar_transform_vector_reverse(double *v, int n);
static void haar_transform_matrix_forward(double **a, int m, int n);
static void haar_transform_matrix_reverse(double **a, int m, int n);
void haar_transform_vector(double *v, int n, int dir);
void haar_transform_matrix(double **a, int m, int n, int dir);

static void haar_transform_vector_forward(double *v, int n) {
    double h = sqrt(n);
    int i, d;
    for (i = 0; i < n; i++)
        v[i] /= h;
    for (d = 1; d < n; d *= 2) {
        for (i = 0; i < n; i += 2*d) {
            double x = SQRT1_2 * (v[i] + v[i+d]);
            double y = SQRT1_2 * (v[i] - v[i+d]);
            v[i] = x;
            v[i+d] = y;
        }
    }
}

static void haar_transform_vector_reverse(double *v, int n) {
    double h = sqrt(n);
    int i, d;
    //moved to the bottom
    for (i = 0; i < n; i++)
        v[i] *= h;
    //swapped d and i's initializations, and have them getting smaller
    for (d = n; d >= 1; d /= 2) {
        for (i = n; i >= 0; i -= 2*d) {
            double x = SQRT1_2 * (v[i] + v[i+d]);
            double y = SQRT1_2 * (v[i] - v[i+d]);
            v[i] = x;
            //added because data was being overwritten in the matrix when i+d >= n
            if (i+d < n)
                v[i+d] = y;
        }
    }
    
}

static void haar_transform_matrix_forward(double **a, int m, int n){
    int i, j;
    //this transforms the rows
    for (i = 0; i < m; i++)
        haar_transform_vector(a[i], n, WT_FWD);
    //this block will take care of transforming the cols
    //create temporary vector for the column
    double *v;
    make_vector(v, m);
    for (j = 0; j < n; j++){
        for (i = 0; i < m; i++){
            //put col values into temp vector
            v[i] = a[i][j];
        }
        //transform the vector
        haar_transform_vector(v, m, WT_FWD);
        //reset values of the matrix's column
        for (i = 0; i < m; i++){
            a[i][j] = v[i];
        }
    }
    free_vector(v);
}

static void haar_transform_matrix_reverse(double **a, int m, int n){
    int i, j;
    //this block will take care of transforming the cols
    //create temporary vector for the column
    double *v;
    make_vector(v, m);
    for (j = 0; j < n; j++){
        for (i = 0; i < m; i++){
            //put col values into temp vector
            v[i] = a[i][j];
        }
        //transform the vector
        haar_transform_vector(v, m, WT_REV);
        //reset values of the matrix's column
        for (i = 0; i < m; i++){
            a[i][j] = v[i];
        }
    }
    free_vector(v);
    //this transforms the rows
    for (i = 0; i < m; i++) {
        haar_transform_vector(a[i], n, WT_REV);
    }
}

void haar_transform_vector(double *v, int n, int dir) {
    if (dir == WT_FWD)
        haar_transform_vector_forward(v, n);
    else if (dir == WT_REV)
        haar_transform_vector_reverse(v, n);
    else { 
        // shouldn’t be here!
        fprintf(stderr, "*** error in haar_transform_vector(): the third argument should be one of WT_FWD or WT_REV\n");
        exit(EXIT_FAILURE);
    }
}

void haar_transform_matrix(double **a, int m, int n, int dir) {
    if (dir == WT_FWD)
        haar_transform_matrix_forward(a, m, n);
    else if (dir == WT_REV)
        haar_transform_matrix_reverse(a, m, n);
    else { 
        // shouldn’t be here!
        fprintf(stderr, "*** error in haar_transform_vector(): the third argument should be one of WT_FWD or WT_REV\n");
        exit(EXIT_FAILURE);
    }
}