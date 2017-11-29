#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#define DEBUGOK


#define MAX_LIST_LEN   1000000
#define MAX_ARR_LEN    10

// assert macro to catch any unexpected inputs and states
#ifdef DEBUGOK
#define assert(CONDITION)                                       \
        if (CONDITION) { } else {                               \
                printf ("Assertion `%s' failed.", #CONDITION);  \
                exit(-1);                                       \
        }
#else
#define assert(CONDITION) 
#endif

struct arr;
struct head;

// Various types of data
typedef enum {
    INFO_CHAR,
    INFO_INT,
    INFO_UINT,
    INFO_FLOAT,
    INFO_DOUBLE,
    INFO_ARRAY,
    INFO_LIST,
    INFO_POINTER
} info_t;

// Linked list data type
typedef struct data {
    info_t   info_type;
    union {
        char         info_char;
        int          info_int;
        unsigned     info_uint;
        float        info_float;
        double       info_double;
        struct arr  *info_array;
        struct head *info_list;
        void        *info_ptr;
    } info;
}  data_t;

// Linked list node type
typedef struct arr {
    data_t   data[MAX_ARR_LEN];
    size_t   len;
} array_t;

// Linked list node type
typedef struct node {
    data_t       data;
    struct node *next;
} node_t;

// Linked list header type
typedef struct head {
    node_t     *first;
    node_t     *last;
    size_t      len;
    //void        (*free_node)(node_t *);
    //node_t     *(*get_node)(data_t);
    //int         (*cmp_fn)(node_t *, node_t *);
} head_t;

typedef int (*cmp_fn_t)( node_t *, node_t *);

// Get a node memory 
node_t *get_node( data_t *d );

// Init a list
void init_list(head_t *head);

// Free a list
void free_list( head_t *head );

// Check if list is empty
bool is_empty( head_t *head);

// Get length of list
size_t get_len( head_t *head );

// Push a node = Insert at front
void insert_atfront( head_t *head, node_t *anode );

// Enqueue a node from rear
void insert_atend( head_t *head, node_t *anode );

// Pop a node = Dequeue a node = Delete from front
node_t *remove_fromfront( head_t *head );

// Dequeue a node = Delete from end
node_t *remove_fromend( head_t *head );

// Insert a node at pos p (1-based)
bool insert_at(head_t *head, size_t p, node_t *anode);

// Delete a node at pos p (1-based)
void delete_at( head_t *head, size_t p );

// Check data of a node at pos p (1-based)
data_t *check_at( head_t *head, size_t p );

// Update a node at pos p (1-based)
bool update_at( head_t *head, size_t p, data_t *d );

// Find node at pos p (1-based)
node_t *find_at( head_t *head, size_t p );

// Find the first position of a given node in a list
bool find_pos( head_t *head, data_t *data_ptr, size_t *pos, size_t start, size_t stop );

// Find and delete a node
bool find_delete( head_t *head, data_t *data_ptr );

// Find and delete all occurences of a node
size_t find_delete_all( head_t *head, data_t *data_ptr );

// Count all occurences of a data item in list
size_t count_all( head_t *head, data_t *data_ptr );

// Print a list
void print_list( head_t *head );

// Slice a list
void slice_list( head_t *head );

// Reverse a linked list using delete and insert
void reverse_list( head_t *head );

// Reverse a linked list, iteratively
void reverse_list_iter( head_t *head );

// Reverse a linked list, recursively
void reverse_list_recur( head_t *head );

// Concatanate two lists: List1 = List1+List2, no separate header for list2 affter concat
void cat_list( head_t *head1, head_t *head2);

// Copy a list between [start,stop), stop not included
// e.g. to copy whole list, pass start=1, and stop=head->len+1
void copy_list1( const head_t *head, head_t *copy_head, size_t start, size_t stop );

// Copy a list
void copy_list( const head_t *head, head_t *copy_head );

// Copy a list, fast
void copy_list_fast( const head_t *head, head_t *copy_head );
 
// Detect a cycle in a list
bool detect_cycle( const head_t *head, size_t *start_pos, size_t *cyc_len );

// Find minimum value in a list
node_t *find_min( head_t *head);

// Find maximum value in a list
node_t *find_max( head_t *head);

// Place a node in a list in sorted order
void insert_inorder( head_t *head, node_t *anode, int order );

// Sort a list using insertion sort
void insert_sort_list( head_t *head, int order );

// Break an input list at pos p into two sublists left and right
void split_list_at( head_t *head_in, size_t pos, head_t *head_l, head_t *head_r);

// Split an input list into two sublists with odd and even pos nodes
void split_alternate( head_t *head_in, head_t *head_o, head_t *head_e); 

// Break an input list into two sublists with first half and second half
void split_list_half( head_t *head_in, head_t *head_f, head_t *head_b);

// Merge two lists into one list by taking nodes from eahc list alternatively
void merge_list_alternate( head_t *head1, head_t *head2, head_t *head_out);

// Sort a list using merge sort
void merge_list_inorder( head_t *head1, head_t *head2, head_t *head_out, int order);

// Sort a list using merge sort, using recursion
void merge_sort_list( head_t *head, int order );

// Check if given list is sorted or not
bool is_list_sorted( const head_t *head, int order );

// Remove duplicate nodes in a sorted list
void unique_list( head_t *head, head_t *head_dup );

// Union and Intersection of two sorted lists, results are sorted as well
size_t union_intersect_list( const head_t *head1, const head_t *head2, head_t *head_u, head_t *head_i, int order );


#endif /*__LINKED_LIST_H__*/
