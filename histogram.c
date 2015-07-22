/*  CS 211 Assignment 4
 *  Use libplot to graphically represent data
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <plot.h>
#include <time.h>
#include "htst.h"

#define MONTHS 12
int calc_max(int data[], int numdata){
	int i=0;
	int max=data[0];
	for(i=1;i<numdata;i++){
		max = (data[i]>max) ? data[i] : max;
	}
	return max;
}
int calc_min(int data[], int numdata){
	int i=0;
	int min=data[0];
	for(i=1;i<numdata;i++){
		min =(data[i]<min) ? data[i] : min;
	}
	return min;
}
int calc_mean(int data[], int numdata){
	int i=0;
	int sum=0;
	int mean=0;
	for(i=0;i<numdata;i++)
		sum += data[i];
	mean = sum/numdata;
	return mean;
}
int cmp(const void *x, const void *y){
	if(*(int *)x > *(int *)y)
		return 1;
	if(*(int *)x<*(int *)y)
		return -1;
	if(*(int *)x==*(int *)y)
		return 0;
}
int calc_mdn(int data[], int numdata){
	int i=0;
        int median=0;
	int dat_temp[numdata];
	memcpy(dat_temp,data,numdata);
	qsort(dat_temp,numdata,sizeof(int),cmp);
	if((numdata%2)==1){
		median=dat_temp[numdata/2+1];
		return median;
	}
	if((numdata%2)==1){
		median=((dat_temp[numdata/2+1]+dat_temp[numdata/2])/2);
		return median;
	}
}
double max_lbl_width(char **str, int numstrs){
	double max_width=pl_flabelwidth(str[0]);
	int i=0;
	for(i=1;i<numstrs;i++)
		max_width = (pl_flabelwidth(str[i])>max_width) ? pl_flabelwidth(str[i]) : max_width;
	return max_width;
}
void draw_rect(int rides, int month, char *mnth)
{
    pl_contrel(0, 0);
    int coord_start = (month - 1) * 500;
    int coord_end = coord_start + 500;
 
    if (month > MONTHS || month < 1){
        fprintf (stderr, "Data includes invalid values\n");
	exit(0);
    }
    else if (pl_box(coord_start, 0, coord_end, rides) < 0){
	fprintf (stderr, "Unable to draw rectangle\n");
	exit(0);
    }
    pl_box(coord_start, 0, coord_end, rides);
    pl_fmove(coord_start+(coord_end-coord_start)/2,rides + 50);
    pl_alabel('c','c',mnth);
    pl_fline(0.0,0.0,10000.0,0.0);	 
    pl_fline(0.0,0.0,0.0,10000.0);
}
void dump_stat_box(int data[], int numdata){
    	pl_fmove(-2500.0,-2500.0);
	pl_alabel('c','x',"Mean is:");
}
int power_ten(int intgr){
	int i=1;
	while(intgr>i)
		i*=10;
}
int make_hist(int data[], int numdata)
{
    //int r_pm[12] = {1234, 1234, 2356, 2345, 5476, 67856, 3456, 34563, 7845, 8456, 3456, 74345};
    char *m[12] = {"Jan.","Feb.","Mar.","Apr.","May","Jun.","Jul.","Aug.","Sep.","Oct.","Nov.","Dec."};  
    char *d[24];
    char *year;
    int handle;
    int i;
    /* set a Plotter parameter */
    pl_parampl ("PAGESIZE", "letter");
    pl_parampl ("BITMAPSIZE", "10000x100000");
    pl_parampl("GIF_ITERATIONS", "0");
    pl_parampl("BG_COLOR", "cyan");
   // pl_parampl("GIF_DELAY","5");    
    /* create a Postscript Plotter that writes to standard output */
    FILE *file=fopen("divvy.gif","w");
    if ((handle = pl_newpl ("gif", stdin,file, stderr)) < 0)
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
     // double shift=max_lbl_width(m,12);
    pl_fspace (-5000.0, -5000.0,25000.0, 25000.0); /* specify user coor system */
    pl_flinewidth (0.25);       /* line thickness in user coordinates */
    pl_pencolorname ("red");    /* path will be drawn in red */
    pl_fmove (0.0, 0.0);    /* position the graphics cursor */
    for(int j=100;j>0;j-=5){
    	pl_erase();
    	for(int i = 0; i < MONTHS; i++){
	    draw_rect(data[i]/j, i + 1,m[i]);
    	}
        dump_stat_box(data,12);
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

