#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "histogram.h"

#define STR_LEN 256

void read_by_day(FILE *file, LIST *list, int month, int day, int year){
	char buffer[STR_LEN];
	char tok_buff[STR_LEN];
	char *token;
	while(!feof(file)){
	  fgets(buffer, STR_LEN, file);
	  strcpy(tok_buff, buffer);
	  token = strtok(tok_buff,"/");
	  if(month == atoi(token)){
	    token = strtok(NULL, "/");
	    if(day == atoi(token)){
		  token = strtok(NULL, " ");
		  if(year == atoi(token)){
		    token = strtok(NULL, ":");
		    add_node(list, month, day, year, atoi(token));
		  }
		}
	  }
    }
}

void read_by_month(FILE *file, LIST *list, int month, int year){
	char buffer[STR_LEN];
	char tok_buff[STR_LEN];
	char *token;
	int day;
	while(fgets(buffer, STR_LEN, file) != NULL){
		fgets(buffer, STR_LEN, file);
		strcpy(tok_buff, buffer);
		token = strtok(tok_buff, "/");
		if(month == atoi(token)){
			token = strtok(NULL, "/");
			day = atoi(token);
			token = strtok(NULL, " ");
			if(year == atoi(token)){
				add_node(list, month, day, year, -1);
			}
		}	
	}
}

void read_by_year(FILE *file, LIST *list, int year){
	char buffer[STR_LEN];
	char tok_buff[STR_LEN];
	char *token;
	int month;
	while(fgets(buffer, STR_LEN, file) != NULL){
		fgets(buffer, STR_LEN, file);
		strcpy(tok_buff, buffer);
		token = strtok(tok_buff, "/");
		month = atoi(token);
		token = strtok(NULL, "/");
		token = strtok(NULL, " ");
		if(year == atoi(token)){
			add_node(list, month, -1, year, -1);
		}	
	}
}

int main(void){
	int counts[31];
	for(int i = 0; i < 31; i++){
	  counts[i] = 0;
	}
	int len;
	int month;
	int day;
	int year;
	char filename[STR_LEN]; 
	char analysis[5];
	LIST *data = list_create();
	printf("Please enter file name containing data to analyze: \n");
	scanf("%s", filename);
	FILE *data_file = fopen(filename, "r");
	if(data_file == NULL){
		fprintf(stderr, "There was an error opening the file.  Make sure it exists.\n");
		exit(0);
	}
	
	printf("How would you like the data to be analyzed?\n Enter \"day\" to analyze the rides per hour in a given day.\n Enter \"month\" to analyze the rides per day in a given month.\n Enter \"year\" to analyze the rides per month in a given year.\n");
	scanf("%s", analysis);
        if(!(strcmp(analysis, "month")==0)){
	    if(!(strcmp(analysis, "day")==0)){
	        if(!(strcmp(analysis, "year")==0)){
		  fprintf(stderr, "Invalid Entry\n");
		  exit(0);
		}
            }
	}
	if(!strcmp(analysis, "day")){
	len = 24;
	printf("Please enter the month (i.e. 02 for February), day (i.e. 15), and year (i.e. 2013) below\n");
	printf("Please enter the month:\n");
	scanf("%i", &month);
	if(month < 0 || month > 12){
	  fprintf(stderr, "Invalid Entry\n");
	  exit(0);
	}
	printf("Please enter the day:\n");
	scanf("%i", &day);
	if(day < 0 || day > 31){
	  fprintf(stderr, "Invalid Entry\n");
	  exit(0);
	}
	printf("Please enter the year:\n");
	scanf("%i", &year);
	if(year < 0 || year > 2099){
	  fprintf(stderr, "Invalid Entry\n");
	  exit(0);
	}
	read_by_day(data_file, data, month, day, year);
  	//count_nodes(data, counts, len);
	//make_hist(counts, len);
}
  
  if(!strcmp(analysis, "month")){
	printf("Please enter the month (i.e. 02 for February), day (i.e. 15), and year (i.e. 2013) below\n");
	printf("Please enter the month:\n");
	scanf("%i", &month);
	if(month < 0 || month > 12){
	  fprintf(stderr, "Invalid Entry\n");
	  exit(0);
	}
	printf("Please enter the year:\n");
	scanf("%i", &year);
	if(year < 0 || year > 2099){
	  fprintf(stderr, "Invalid Entry\n");
	  exit(0);
	}
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
		len = 31;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11){
		len = 30;
	}
	else if (month == 2 && year%4 == 0){
		len = 29;
	}
	else{
		len = 28;
	}
	read_by_month(data_file, data, month, year);
  	count_nodes(data, counts, len);
	make_hist(counts, len);
}
  
  if(!strcmp(analysis, "year")){
	len = 12;
	printf("Please enter the year:\n");
	scanf("%i", &year);
	if(year < 0 || year > 2099){
	  fprintf(stderr, "Invalid Entry\n");
	  exit(0);
	}
	read_by_year(data_file, data, year);
	count_nodes(data, counts, len);
	make_hist(counts, len);
  }
  list_free(data);
  return 0;
}

