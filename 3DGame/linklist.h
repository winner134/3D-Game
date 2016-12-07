/*------------- LINKLIST.H -------------- */
/* Public part of the linear list ADT */
/* Provides ADT: List of Integers */
//#include "genlib.h"
/* type declaration */
typedef struct list_format *List;
/* make explicity the base type */
typedef int ElementType;

/* -- for convenience: special type for pointers to nodes */
typedef struct node_type *Node;

/* ------- Operations --------- */
/* Constructors */
List CreateList ();
/* Destructors */
void DestroyList (List l);
/* Inspectors */
/* compute size of the list */
int ListSize (List l);
/* is the list empty ? */
int EmptyList (List l);

/* select element in the list via index */
Node SelectInList (int index, List l);

/* Modifiers */
/* insert a new element in a given position */
int InsertInList (int index, float initial_bullet_x,
	float initial_bullet_y,
	float initial_bullet_z,
	float translate_bullet_x,
	float translate_bullet_y,
	float translate_bullet_z,
	float bullet_angle_x,
	float bullet_angle_y,
	float bullet_angle_z, List l);
/* delete element from list */
int DeleteInList (int index, List l);

/* ---- END OF LIST.h ----- */
