/*  CS 211 Assignment 4
 *  Use libplot to graphically represent data
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <plot.h>
#include <time.h>
#include "histogram.h"

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
void draw_rect(int rides, int inc, char *mnth)
{
    //int increments = 0;
    pl_contrel(0, 0);
    int coord_start = (inc - 1) * 500;
    int coord_end = coord_start + 500;
 
    if (inc > 31 || inc < 1){
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
    //int increments = 0;
    char *m[12] = {"Jan.","Feb.","Mar.","Apr.","May","Jun.","Jul.","Aug.","Sep.","Oct.","Nov.","Dec."};  
    char *h[24] = {"1:00","2:00","3:00","4:00","5:00","6:00","7:00","8:00","9:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00","17:00","18:00","19:00","20:00","21:00","22:00","23:00","24:00"};
    char *d[31]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31"};
    char *year;
    char **inc;
    int handle;
    int i;
    if(numdata > 24){
	inc = d;
        //increments = 31;
    }
    else if(numdata == 24){
 	inc = h;
        //increments = 24; 
    }
   else if(numdata == 12){
	inc = m;
        //increments = 12;
    }
   else{
	fprintf(stderr, "Invalid flag.\n\n");
	exit(0);
    }
    /* set a Plotter parameter */
    pl_parampl ("PAGESIZE", "letter");
    pl_parampl ("BITMAPSIZE", "10000x100000");
    pl_parampl("GIF_ITERATIONS", "0");
    pl_parampl("BG_COLOR", "Mint Cream");
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
    pl_pencolorname ("black");    /* path will be drawn in red */
    pl_fmove (0.0, 0.0);    /* position the graphics cursor */
    pl_fillcolorname("Powder Blue");
    for(int j=100;j>0;j-=5){
    	pl_erase();
    	for(int i = 0; i < numdata; i++){
	    draw_rect(data[i]/j, i + 1,inc[i]);
    	}
        //dump_stat_box(data,INCREMENTS);
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

