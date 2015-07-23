/*  CS 211 Assignment 4
 *  Use libplot to graphically represent data
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <plot.h>
#include <time.h>

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
	while(i<numdata){
		dat_temp[i]=data[i];
		i++;
	}
	qsort(dat_temp,numdata,sizeof(int),cmp);
	if((numdata%2)==1){
		median=dat_temp[numdata/2+1];
		return median;
	}
	if((numdata%2)==0){
		median=((dat_temp[numdata/2]+dat_temp[numdata/2-1])/2);
		return median;
	}
}
void draw_rect(double rides, double incrmt, char *lbl, double max, int numdata)
{
    pl_fmove(1.0, 4.75);
    double coord_start = 1.0+(incrmt - 1.0) * (6.5/numdata);
    double coord_end = coord_start + (6.5/numdata);
    double height=rides*(5.75/max);
    if (incrmt > numdata || incrmt < 1){
        fprintf (stderr, "Data includes invalid values\n");
	exit(0);
    }
    else if (pl_fbox(coord_start, 4.75, coord_end, height+4.75) < 0){
	fprintf (stderr, "Unable to draw rectangle\n");
	exit(0);
    }
    pl_fbox(coord_start, 4.75, coord_end, height+4.75);
    pl_fmove(coord_start,4.25);
    pl_alabel('l','l',lbl);
    pl_fline(1.0,4.75,1.0,10.5);	 
    pl_fline(1.0,4.75,7.5,4.75);
}
void dump_stat_box(int data[], int numdata){
	char buf[200];
        int stat=0;
	stat=calc_mean(data,numdata);
        sprintf(buf, "The mean value is: %d.\n%c",stat,'\0');    
	pl_fmove(1.0,3.0);
	pl_alabel('l','x',buf);
	stat=calc_mdn(data,numdata);
	sprintf(&buf[0], "The median value is: %d.\n%c",stat,'\0');
	pl_fmove(1.0,2.75);
	pl_alabel('l','x',buf);
	stat=calc_min(data,numdata);
        sprintf(&buf[0], "The minimum value is: %d.\n%c",stat,'\0');
        pl_fmove(1.0,2.50);
        pl_alabel('l','x',buf);
	stat=calc_max(data,numdata);
        sprintf(&buf[0], "The maximum value is: %d.\n%c",stat,'\0');
        pl_fmove(1.0,2.25);
        pl_alabel('l','x',buf);
}
int make_hist(int data[], int numdata, int month, int day, int year)
{
    char *m[12] = {"Jan.","Feb.","Mar.","Apr.","May","Jun.","Jul.","Aug.","Sep.","Oct.","Nov.","Dec."};  
    char *h[24] = {"0","1", "2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23"};
    char *d[31] = {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31"};
    char **inc;
    char *type;
    char buf[200];
    int handle;
    int i;
    int max_rides=0;
    if(numdata > 24){
        inc = d;
	type="days of the month.";
    }
    else if(numdata == 24){
        inc = h;
	type="hours of the day.";
    }
   else if(numdata == 12){
        inc = m;
	type="months of the year.";
    }
   else{
        fprintf(stderr, "Invalid flag.\n\n");
        exit(0);
    }            
    pl_parampl ("PAGESIZE", "letter,xsize=8.5in,ysize=11in,xorigin=0in,yorigin=0in");
    pl_parampl("GIF_ITERATIONS", "0");
    pl_parampl("BG_COLOR", "Mint Cream");
    
    FILE *file=fopen("divvy.gif","w");
    if ((handle = pl_newpl ("gif", stdin,file, stderr)) < 0)
    {
        fprintf (stderr, "Couldn't create Plotter\n");
        return 1;
    }
    pl_selectpl (handle);       
    if (pl_openpl () < 0)      
    {
        fprintf (stderr, "Couldn't open Plotter\n");
        return 1;
    }
  
    max_rides=calc_max(data,numdata);
    pl_fspace (0.0,0.0,8.5,11.0); 
    pl_flinewidth (0.009);       
    pl_pencolorname ("black");    
    pl_fmove (1.0,4.25);    
    pl_filltype(1);
    pl_fillcolorname("powder blue"); 
    for(int j=1073741824;j>0;j/=2){
    	pl_erase();
    	for(int i = 0; i < numdata; i++){
	    draw_rect((double)data[i]/(double)j,(double)i + 1.0,inc[i],(double)max_rides,numdata);
    	}
    }
    pl_fmove(1.0,4.75);
    for(int i=1;i<=10;i++){
        pl_fmove(1.0,4.75+i*(5.75/10));
	sprintf(&buf[0],"%d%c",(max_rides/10)*i,'\0');
	pl_alabel('r','r',buf);
    }
    sprintf(buf,"Histogram for %s.%c",type,'\0');
    pl_fmove(3.0,10.5);
    pl_alabel('l','l',buf);
    dump_stat_box(data,numdata);
    if (pl_closepl () < 0) 
    {
        fprintf (stderr, "Couldn't close Plotter\n");
        return 1;
    }
    
    pl_selectpl (0);            
    if (pl_deletepl (handle) < 0) 
    {
        fprintf (stderr, "Couldn't delete Plotter\n");
        return 1;
    }

    return 0;
}

