/*  CS 211 Assignment 4
 *  Use libplot to graphically represent data
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <plot.h>
#include <time.h>

int calc_max(int data[], int numdata){ //Gets the maximum value in the array
	int i=0;
	int max=data[0];
	for(i=1;i<numdata;i++){
		max = (data[i]>max) ? data[i] : max;
	}
	return max;
}
int calc_min(int data[], int numdata){ //Gets the minimum value in the array
	int i=0;
	int min=data[0];
	for(i=1;i<numdata;i++){
		min =(data[i]<min) ? data[i] : min;
	}
	return min;
}
int calc_mean(int data[], int numdata){ //Calculates the mean value of the data in the array
	int i=0;
	int sum=0;
	int mean=0;
	for(i=0;i<numdata;i++)
		sum += data[i];
	mean = sum/numdata;
	return mean;
}
int cmp(const void *x, const void *y){ //Comparison function for qsort call in median function
	if(*(int *)x > *(int *)y)
		return 1;
	if(*(int *)x<*(int *)y)
		return -1;
	if(*(int *)x==*(int *)y)
		return 0;
}
int calc_mdn(int data[], int numdata){ //Calculates the median value of the data
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
void draw_rect(double rides, double incrmt, char *lbl, double max, int numdata) //Draws the bars of the histogram, and draws the axes
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
    pl_fmove(coord_start,4.35);
    if(numdata != 12){
      pl_ffontsize(.17);
      pl_alabel('1','1',lbl);
      pl_ffontsize(.22);
    }
    else{
      pl_alabel('l','l',lbl);
    }
    pl_fline(1.0,4.75,1.0,10.5);	 
    pl_fline(1.0,4.75,7.5,4.75);
}
void dump_stat_box(int data[], int numdata){ //Puts statistical information onto the display
	char buf[200];
	int (*stat[4])(int *,int)={calc_mean, calc_mdn,calc_min,calc_max};
        char *strs[4]={"mean", "median", "minimum", "maximum"};
        for(int i=0;i<4;i++){
                sprintf(buf, "The %s value is: %d.\n%c",strs[i],stat[i](data,numdata),'\0');
                pl_fmove(1.0,3.0-(0.25)*i);
                pl_alabel('l','x',buf);
        }
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
    /*Determine the category by which to display.*/
    if(numdata > 24){
        inc = d;
	type="Days of the Month";
    }
    else if(numdata == 24){
        inc = h;
	type="Hours of the Day";
    }
   else if(numdata == 12){
        inc = m;
	type="Months of the Year";
    }
   else{
        fprintf(stderr, "Invalid flag.\n\n");
        exit(0);
    }            
    /*Set the page attributes.*/
    pl_parampl ("PAGESIZE", "letter,xsize=8.5in,ysize=11in,xorigin=0in,yorigin=0in");
    pl_parampl("GIF_ITERATIONS", "0");
    pl_parampl("BG_COLOR", "Mint Cream");
    FILE *file=fopen("divvy.gif","w"); //Outputs the display to a file called divvy.gif
    if ((handle = pl_newpl ("gif", stdin, file, stderr)) < 0)
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
  /*Calculate the maximum number of rides, set the drawing attributes, and draw each frame of the animation*/
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
    pl_fmove(.75,4.75);
    for(int i=1;i<=10;i++){ //This is where the animation happens.
        pl_fmove(1.0,4.75+i*(5.75/10));
	sprintf(&buf[0],"%d%c",(max_rides/10)*i,'\0');
	pl_alabel('r','r',buf);
    }
    /*Generate the title.*/
    if (numdata == 12){
      sprintf(buf, "Histogram for %s: %d.%c", type, year, '\0');
    }
    else if (numdata == 24){
      sprintf(buf, "Histogram for %s: %d/%d/%d.%c", type, month, day, year, '\0');
    }
    else{
      sprintf(buf, "Histogram for %s: %d/%d.%c", type, month, year, '\0');
    }
    pl_fmove(2.5,10.75);
    pl_alabel('l','l',buf);
    pl_textangle(90);
    pl_fmove(0.15,7.75);
    pl_alabel('c','x',"Rides");
    pl_textangle(0);
    pl_fmove(4.0,3.75);
    pl_alabel('c','c',type);
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
    fclose(file);
    return 0;
}

