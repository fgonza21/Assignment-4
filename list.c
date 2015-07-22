#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "list.h"


LIST *list_create()
{
	LIST *new_list = malloc(sizeof(LIST));

	new_list->front = NULL;
	new_list->back = NULL;
	return new_list;
}	

void list_free(LIST *list)
{
	NODE *temp = list->front;
	NODE *temp_next;

	while(temp != NULL) {
     	temp_next = temp->next;   
		free(temp);
		temp = temp_next;
  	}
    	free(list);
}

void print_lst( LIST* list)
{
	NODE *p = list->front; 
	while( p != NULL)
	{
		printf("list hour: %i day: %i month %i year %i\n", p->hour, p->day, p->month, p->year); 
		p = p->next; 
	}
}

void add_node( LIST* list , int val_month, int val_day, int val_year, int val_hour ) 
{
	NODE *temp_node;

	if( list->back == NULL)
	{
		temp_node = malloc(sizeof(NODE));
		temp_node->month = val_month;
		temp_node->day = val_day; 
		temp_node->year = val_year; 
	 	temp_node->hour = val_hour;
		temp_node->next = NULL;
		list->front= temp_node;
		list->back = temp_node;
		return;
	}

	temp_node = malloc(sizeof(NODE));
	temp_node->month = val_month;
	temp_node->day = val_day; 
	temp_node->year = val_year; 
	temp_node->hour = val_hour; 
	temp_node->next = NULL;
	list->back->next=temp_node;
	list->back = temp_node;

}
  	

void count_node( LIST *list, int *count_array, char *type)
{
	NODE *p = list->front;
	while(p != NULL) 
	{
	 	if(!(strcmp(type, "day"))==0)
	 	{
			count_array[p->hour]++;
	 	}	
	 	else if(!(strcmp(type, "month"))==0)
	 	{
			count_array[p->day - 1]++;
		}	
		 else if(!(strcmp(type, "year"))==0)
	 	{
			count_array[p->month - 1]++;
	 	}	  
	}
}	
	
void free_node(NODE *node)
{
	while(node != NULL)
	{
		NODE *temp_node = NULL; 
   		temp_node = node; 
   		node = node->next;
  		free(node);
	 }
}
