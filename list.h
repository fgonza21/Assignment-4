typedef struct node{
  struct node *next;
  int hour;
  int day;
  int month;
  int year;
}NODE;

typedef struct{
  NODE *front;
  NODE *back;
}LIST;

LIST *list_create();

//void print_lst( LIST* list);

void list_free(LIST *list);

void add_node( LIST* list , int val_month, int val_day, int val_year, int val_hour);

void count_nodes( LIST *list , int *count_array , int type);

void free_node( NODE *node);


