/* world-to-eps.c
 *
 * This file is a part of /Project Evolution/ in Chapter 17 of
 * Programming Projects in C
 * http://userpages.umbc.edu/~rostamia/cbook/
 *
 * Rouben Rostamian <rostamian@umbc.edu>
 * 2012-11-11
 */

#include <stdio.h>
#include "world-to-eps.h"

/* S sets the length (in PostScript points) of the larger side
 * (width or height) of the drawn image.  The image's other side
 * is scaled so that to give it the same aspect ratio as the World.
 *
 * When the EPS file is converted to a raster format, the 512 points
 * is converted to 512 pixels.
*/
#define S	512

/* Writes a snapshot of the simulated world as an
 * Encapsulated PostScript (EPS) image into the specified file.
 */
void world_to_eps(struct world *world, char *epsfile)
{
	FILE *fp;
	double scale, food_size, anim_size;
	conscell *p;
	int i, j;

	if (world->world_w >= world->world_h)
		scale = (double)S / world->world_w;
	else
		scale = (double)S / world->world_h;

	food_size = 0.12*scale;	/* radius of a food disk */
	anim_size = 0.09*scale;	/* radius of an animal disk */

	fp = fopen(epsfile, "w");
	if (fp == NULL) {
		fprintf(stderr, "unable to open file %s for writing\n",
				epsfile);
		return;
	}


	/* Postscript header */
	fputs("%%!PS-Adobe-3.0 EPSF-3.0\n", fp);
	fputs("%%%%Title: (Evolution)\n", fp);
	fputs("%%%%Creator: Rouben Rostamian <rostamian@umbc.edu>\n", fp);
	fputs("%%%%BoundingBox: ", fp);
	fprintf(fp, "%d %d %d %d\n", 0, 0,
			(int)(scale * world->world_w), (int)(scale * world->world_h));
	/*
	fputs("%%DocumentFonts: Times-Roman Times-Bold "
			"Times-Italic Helvetica\n", fp);
	*/
	fputs("%%EndComments\n\n", fp);

	fputs("2 dict begin\n", fp);
	fputs("/origstate save def\n", fp);

	/* set scale */
	fprintf(fp, "%g %g scale\n", scale, scale);

	/* rounded caps */
	fprintf(fp, "%d setlinecap\n", 1);

	/* Define a function to draw points; takes x, y, r from stack. */
	fprintf(fp, "/d {0 360 arc fill} def\n");

	/* draw canvas */
	fputs("1.0 1.0 1.0 setrgbcolor\n", fp);
	fprintf(fp, "newpath 0 0 moveto %d 0 lineto %d %d lineto "
			"0 %d lineto closepath fill\n",
			world->world_w, world->world_w, world->world_h, world->world_h);

	/* draw Eden */
	fprintf(fp, "%.3f %.3f %.3f setrgbcolor\n",
			225./255, 245./255, 225./255); // home-made
	fprintf(fp, "newpath %d %d moveto %d 0 rlineto 0 %d rlineto "
			"%d 0 rlineto closepath fill\n",
			(world->world_w - world->eden_w)/2, (world->world_h - world->eden_h)/2, 
			world->eden_w, world->eden_h, -world->eden_w);


	/* draw food morsels */
	fprintf(fp, "%.3f %.3f %.3f setrgbcolor\n",
			154./255, 205./255, 50./255); // YellowGreen
	for (i = 0; i < world->world_h; i++)
		for (j = 0; j < world->world_w; j++)
			if (world->plants[i][j] > 0)
				fprintf(fp, "%d %d %g d\n", j, i,
						food_size*world->plants[i][j]);

	/* draw animals */
	fprintf(fp, "%.3f %.3f %.3f setrgbcolor\n",
			178./255, 34./255, 34./255); // firebrick
	for (p = world->herd; p != NULL; p = p->next) {
		struct animal *a = p->data;
		fprintf(fp, "%d %d %g d\n", a->j, a->i, anim_size);
	}

	/* finish up */
	fputs("showpage\n", fp);
	fputs("origstate restore\n", fp);
	fputs("end % dict\n", fp);
	fputs("%%EOF\n", fp);
	fclose(fp);
}
