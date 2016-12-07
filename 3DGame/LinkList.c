/*--------------------- LINKLIST.C ------------------------*/
/* Implementation of the List ADT */
/* Using linked lists */
/*-----------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
//#include "genlib.h"
#include "linklist.h"

/* ------------ Type declarations --------------- */
/* -- this is the structure representing one node of the sequence */
typedef struct node_type {
float initial_bullet_x;
float initial_bullet_y;
float initial_bullet_z;
float translate_bullet_x;
float translate_bullet_y;
float translate_bullet_z;
float bullet_angle_x;
float bullet_angle_y;
float bullet_angle_z;
struct node_type *next;
} basic_node;


/* -- this is the structure representing the metadata of the list */
typedef struct list_format {
int size;
basic_node *first;
basic_node *pos;
} basic_list;
/*----------------- Functions ------------------- */
/*-------- OPERATIONS --------*/
/* CreateList: produce a new empty list */
List CreateList ()
{
List new1;
/* allocate space for the metadata of the list */
new1 = (basic_list *) malloc (sizeof(basic_list));
if (new1 == NULL)
{
printf("Unable to create list\n");
return NULL;
}
/* initialize the fields */
new1->size = 0;
new1->first = NULL; /* no elements in the sequence */
new1->pos = NULL;
return new1;
}
/* DestroyList: release the space occupied by the list */
void DestroyList(List l)
{
int i;
Node temp,scan;
/* need to remove each element in the sequence */
scan = l->first;
for (i=0; i < l->size; i++)
{
temp = scan;
scan = scan->next;
free(temp);
}
/* finally need to remove the list metadata */
free(l);
}
/* ListSize: compute the number of elements in the input list */
int ListSize (List l)
{
return l->size;
}
/* EmptyList: verifies whether the list is empty or not */
int EmptyList (List l)
{
return (l->size == 0);
}

/* SelectInList: accepts a list and an index. If index is a legal
value (i.e., less than the size of the list, then the function
returns the element store in that position in the list, otherwise
produces -1
The operation also sets the pos field of the metadata */
Node SelectInList (int index, List l)
{
int i;
Node scan;
if (index > l->size || index < 1)
{
l->pos = NULL;
return NULL; /* index is out of range */
}
scan = l->first;
for (i = 1; i < index; i++)
scan = scan->next;
l->pos = scan;
return scan;
}

/* InsertInList: takes a list, an index, and an element. It stores the
element in the position index of the list (if index is a legal value).
returns TRUE if successful, FALSE otherwise */
int InsertInList (int index, float initial_bullet_x,
	float initial_bullet_y,
	float initial_bullet_z,
	float translate_bullet_x,
	float translate_bullet_y,
	float translate_bullet_z,
	float bullet_angle_x,
	float bullet_angle_y,
	float bullet_angle_z, List l)
{
int i;
Node scan,prev;
Node new1;
/* verifies that the index is legal */
if (index < 1 || index > l->size+1)
return 0; /* index out of range */
/* create the new element */
new1 = (basic_node*) malloc(sizeof(basic_node));
new1->initial_bullet_x = initial_bullet_x;
new1->initial_bullet_y = initial_bullet_y;
new1->initial_bullet_z = initial_bullet_z;
new1->translate_bullet_x = translate_bullet_x;
new1->translate_bullet_y = translate_bullet_y;
new1->translate_bullet_z = translate_bullet_z;
new1->bullet_angle_x = bullet_angle_x;
new1->bullet_angle_y = bullet_angle_y;
new1->bullet_angle_z = bullet_angle_z;
if (index == 1) // insert first element
{
new1->next = l->first;
l->first = new1;
}
else
{
SelectInList(index-1,l);
new1->next = l->pos->next;
l->pos->next = new1;
}
l->size++;
return 1;
}
/* DeleteInList: deletes the element in position index of the list
returns TRUE if successful and FALSE if fails */
int DeleteInList (int index, List l)
{
int i;
Node scan,prev;
if (l->size == 0)
return 0; /* list is empty, nothing to delete */
if (index < 1 || index > l->size)
return 0; /* index out of range */
/* find the element to remove */
if (index == 1) // remove first element
{
scan = l->first;
l->first = l->first->next;
}
else
{
SelectInList(index-1,l);
scan = l->pos->next;
l->pos->next = scan->next;
}
free(scan);
l->size--;
return 1;
}