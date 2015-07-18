/*  CS 211 Assignment 4
 *  Use libplot to graphically represent data
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <plot.h>

#define MONTHS 12

void draw_rect(int rides, int month)
{
    pl_contrel(0, 0);
    int coord_start = (month - 1) * 50;
    int coord_end = coord_start + 50;
 
    if (month > MONTHS || month < 1){
        fprintf (stderr, "Data includes invalid values\n");
	exit(0);
    }
    else if (pl_box(coord_start, 0, coord_end, rides) < 0){
	fprintf (stderr, "Unable to draw rectangle\n");
	exit(0);
    }
    pl_box(coord_start, 0, coord_end, rides);
	 
}

int main ()
{
    int r_pm[12] = {1234, 1234, 2356, 2345, 5476, 67856, 3456, 34563, 7845, 8456, 3456, 74345};

    for(int i = 0; i < MONTHS; i++){
      r_pm[i] = r_pm[i]/10;
    }
    
    int handle;
    
    /* set a Plotter parameter */
    pl_parampl ("PAGESIZE", "letter");
    
    /* create a Postscript Plotter that writes to standard output */
    if ((handle = pl_newpl ("gif", stdin, stdout, stderr)) < 0)
    {
        fprintf (stderr, "Couldn't create Plotter\n");
        return 1;
    }
    pl_selectpl (handle);       /* select the Plotter for use */
    
    if (pl_openpl () < 0)       /* open Plotter */
    {
        fprintf (stderr, "Couldn't open Plotter\n");
        return 1;
    }
    pl_fspace (0.0, 0.0, 10000.0, 10000.0); /* specify user coor system */
    pl_flinewidth (0.25);       /* line thickness in user coordinates */
    pl_pencolorname ("red");    /* path will be drawn in red */
    pl_erase ();                /* erase Plotter's graphics display */
    pl_fmove (0.0, 0.0);    /* position the graphics cursor */

    for(int i = 0; i < MONTHS; i++){
      draw_rect(r_pm[i], i + 1);
    }

    if (pl_closepl () < 0)      /* close Plotter */
    {
        fprintf (stderr, "Couldn't close Plotter\n");
        return 1;
    }
    
    pl_selectpl (0);            /* select default Plotter */
    if (pl_deletepl (handle) < 0) /* delete Plotter we used */
    {
        fprintf (stderr, "Couldn't delete Plotter\n");
        return 1;
    }
    return 0;
}

