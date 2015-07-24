/*
 * list.c: This file is used as Abstract Data Type (ADT) for the user
 * program 
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "list.h"

/*
 *    function:  list_create  
 *     description: returns pointer to newly created empty list
*/
LIST *list_create()
{
	LIST *new_list = malloc(sizeof(LIST));
	new_list->front = NULL;
	new_list->back = NULL;
	return new_list;
}	

/*
 *    function:  list_free  
 *    parameter: LIST *list
 *    description: dellocates the meonory associated with the list 
*/
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


/* 	function: add_node
 *  	parameters: LIST* list , int val_month, int val_day, int val_year, int val_hour
 *  	description: adds a node to the list with vraibles that represent the 
 * 		month, day, year and hour which the user program specifies though 
 * 		providing the vriables in the parameters. 
 * 
*/

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
  	
/*
 *    function:  count_nodes
 *    parameters:  LIST *list, int *count_array, int type
 *    description:  Counts number of occurrences 
 *     		of type (month, day, year, hour) in the list and returns 
 *     		that value.
*/
void count_nodes( LIST *list, int *count_array, int type)
{
	NODE *p = list->front;
	while(p != NULL) 
	{
	 	if(type == 12)
	 	{
			count_array[p->month -1]++;
	 	}	
	 	else if(type == 24)
	 	{
			count_array[p->hour]++;
		}	
		 else 
	 	{
		  	count_array[p->day - 1]++;
	 	}
	p = p->next;	  
	}
}	

/*
 *    function:  free_node 
 *    parameters:  NODE *node
 *    description:  Deallocates all the nodes in the list 
 *     and the list itself by calling the free. 
*/	
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
