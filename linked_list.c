/********************************************************************
  Author: Vikas YADAV (vikasy@gmail.com)
  Filename: linked_list.c
  Topic: Implementaton of various linked list related functions
   
  Objective: Implement a host of linked list related functions.
  
  ***********************************************************************/
  #include "linked_list.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

static void get_fmt_str(char *fmt_str, info_t data_type);

// Get a node memory 
node_t *get_node( data_t *d )
{
    node_t *retptr = malloc( sizeof(*retptr) );
    if( retptr == NULL )
        return NULL;
    retptr->data = *d;
    retptr->next = NULL;
    return retptr;
}

// Compare two list nodes
bool cmp_fn( const data_t *d1, const data_t *d2, int *retval)
{
    if( d1==NULL || d2==NULL || d1->info_type!=d2->info_type )
        return false;

    switch( d1->info_type ) {
        case INFO_INT:
            *retval = d1->info.info_int - d2->info.info_int;
            break;
        default:
            break;
    }
    return true;
}

// Init a list
void init_list( head_t *head )
{
    if(head==NULL) {
        printf("ERR:Null ptr\n");
        return;
    }
    head->first = head->last = NULL;
    head->len = 0;
}

// Free a list, does nto free head as it could be on stack
void free_list( head_t *head )
{
    node_t *tofree = NULL;
    char    fmt_str[2] = { 0 };

    while( head!= NULL && head->len > 0 ) {
        tofree = head->first;
        head->first = head->first->next;
        head->len--;
        get_fmt_str( fmt_str, tofree->data.info_type);
        if (fmt_str[0] == 1) {
            free_list(tofree->data.info.info_list);
            free(tofree);
        }
        //else if( fmt_str[0] == 2 ) 
        //    free_array(temp_ptr->data);
        //else if( fmt_str[0] == 3 ) 
        //    free_ptr(temp_ptr->data);
        else {
            free(tofree);
        }
    }
}

// Check if list is empty
bool is_empty( head_t *head)
{
    return head->len == 0;
}

// Check if list is full
bool is_full( head_t *head)
{
    return head->len >= MAX_LIST_LEN;
}

// Get length of list
size_t get_len( head_t *head )
{
    return head->len;
}

// Push a node = Insert at front
void insert_atfront( head_t *head, node_t *anode )
{
    assert( head != NULL );
    
    if( anode == NULL )
        return;

    anode->next = head->first;
    head->first = anode;
    head->len++;
    if( head->last == NULL )
        head->last = anode;

}

// Enqueue a node from rear
void insert_atend( head_t *head, node_t *anode )
{
    assert( head != NULL );
    
    if( anode == NULL )
        return;

    if( head->last == NULL )
        head->first = anode;
    else 
        head->last->next = anode;
    anode->next = NULL;
    head->last = anode;
    head->len++;
}

// Pop a node = Delete from front
// return NULL if list is empty
node_t *remove_fromfront( head_t *head )
{
    node_t *retptr = NULL;
    assert( head != NULL );

    retptr = head->first;
    if( head->first != NULL ) {
        head->first = head->first->next;
        head->len--;
    }
    if( head->first == NULL ) 
        head->last = NULL;

    return retptr;
}

// Dequeue a node = Delete from end
// return NULL if list is empty
node_t *remove_fromend( head_t *head )
{
    node_t *retptr = NULL;
    node_t *prevptr = NULL;
    assert( head != NULL );

    retptr = head->first;
    while( retptr != head->last ) {
        prevptr = retptr;
        retptr = retptr->next;
    }
    head->last = prevptr;
    if( prevptr != NULL ) {
        prevptr->next = NULL;
        head->len--;
    }

    return retptr;
}

// Insert a node at pos p (1-based)
bool insert_at( head_t *head, size_t p, node_t *anode )
{
    node_t *temp = NULL;
    assert( head != NULL );
    
    if( anode == NULL )
        return true;
    
    if( p == 0 ) 
        return false;
    else if( p == 1 && head->len == 0 ) {
        // insert at 1st node in an empty list
        head->last = head->first = anode;
        anode->next = NULL;
        head->len++;
    }
    else if( p == head->len ) {
        // insert at the end
        if( head->last == NULL )
            head->first = anode;
        else 
            head->last->next = anode;
        head->last = anode;
        anode->next = NULL;
        head->len++;
    }
    else if( p > head->len ) 
        return false;
    else {
        // insert in the middle
        temp = head->first;
        while( --p ) {
            temp = temp->next;
        }
        // need to insert between temp and temp->next
        anode->next = temp->next;
        temp->next = anode;
        head->len++;
    }
    return true;
}

// Remove a node at pos p (1-based)
node_t *remove_at( head_t *head, size_t p )
{
    node_t *retptr = NULL, *temp_ptr=NULL;
    
    assert( head != NULL );
    
    if( p == 0 ) 
        return NULL;
    else if( p == 1 && head->len == 1 ) {
        // remove 1st node of a one node list 
        retptr = head->first;
        head->last = head->first = NULL;
        retptr->next = NULL;
    }
    else if( p == head->len ) {
        // remove the last node
        retptr = head->first;
        while( --p > 1 ) {
            retptr = retptr->next;
        }
        head->last = retptr;
        retptr = retptr->next;
        retptr->next = NULL;
    }
    else if( p > head->len ) 
        return NULL;
    else {
        // remove from the middle
        retptr = head->first;
        while( --p > 1 ) {
            retptr = retptr->next;
        }
        temp_ptr = retptr->next;
        retptr->next = retptr->next->next;
        retptr = temp_ptr;
        temp_ptr->next = NULL;
    }
    head->len--;
    return retptr;
}

// Delete a node at pos p (1-based)
void delete_at( head_t *head, size_t p )
{
    node_t *ret_ptr = NULL;
    ret_ptr = remove_at(head, p);
    if( ret_ptr!= NULL )
        head->len--;
    free(ret_ptr);
}

// Find node at pos p (1-based)
node_t *find_at( head_t *head, size_t p )
{
    node_t *retptr = NULL;
    assert( head != NULL );
    
    if( p == 0 || p > head->len+1 ) 
        return NULL;
    else {
        retptr = head->first;
        while( --p ) {
            retptr = retptr->next;
        }
    }

    return retptr;
}

// Check data of a node at pos p (1-based)
data_t *check_at( head_t *head, size_t p )
{
    node_t *retptr = NULL;
    retptr = find_at( head, p);
    if( retptr == NULL ) 
        return NULL;
    return &retptr->data;
}

// Update data of a node at pos p (1-based)
bool update_at( head_t *head, size_t p, data_t *d )
{
    node_t *retptr = NULL;

    retptr = find_at( head, p);
    if( retptr == NULL ) 
        return false;

    retptr->data = *d;
    return true;
}

// Find the first position (1-based) of a given data item in list
// search for given node between [start,stop) stop not included
// e.g. to search whole list, pass start=1, and stop=head->len+1
bool find_pos( head_t *head, data_t *data_ptr, size_t *pos, size_t start, size_t stop )
{
    size_t  index = 1;
    node_t *temp = NULL;
    int     retval = 0;

    assert( head!=NULL && data_ptr!=NULL && pos!=NULL );

    temp = head->first;
    if( start==0 || stop==0 || start > head->len || stop > head->len+1 || start >= stop ) {
        printf("Inconsistent start=%"PRIu64" and stop=%"PRIu64" [list len=%"PRIu64"]",
                (unsigned long long)start,(unsigned long long)stop,(unsigned long long)head->len);
        return false;
    }
    // return false for empty list as well
    if(  temp == NULL )
        return false;

    // skip all nodes before start pos
    while( index < start ) {
        temp = temp->next;
        index++;
    }

    // search for given node between [start,stop) stop not included
    while( index <stop ) {
        if( cmp_fn( &temp->data, data_ptr, &retval) == false )
            return false;
        if( retval == 0 ) {
            *pos = index;
            return true;
        }
        temp = temp->next;
        index++;
    }
    return false;
}

// Find and delete the first occurences of a data item in list
bool find_delete( head_t *head, data_t *data_ptr )
{
    size_t pos = 0;
    bool   retval = true;
    retval = find_pos(head, data_ptr, &pos, 0, head->len);
    if( retval )
        delete_at(head, pos);
    return retval;
}

// Find and delete all occurences of a data item in list
size_t find_delete_all( head_t *head, data_t *data_ptr )
{
    size_t pos = 0;
    bool   retval = true;
    size_t count = 0;
    while( retval ) {
        retval = find_pos(head, data_ptr, &pos, 0, head->len);
        if( retval ) {
            delete_at(head, pos);
            count++;
        }
    }
    return count;
}

// Count all occurences of a data item in list
size_t count_all( head_t *head, data_t *data_ptr )
{
    node_t *inode = NULL;
    int     retval = 0;
    size_t  count = 0;

    for( inode = head->first; inode!=NULL; inode=inode->next ) {
        if( cmp_fn( &inode->data, data_ptr, &retval) == false )
            return 0;
        if( retval == 0 )
            count++;
    }

    return count;
}

static void get_fmt_str( char *fmt_str, info_t data_type )
{
    fmt_str[0] = 0;
    fmt_str[1] = 0;
    switch( data_type ) {
    case INFO_CHAR: fmt_str[0] = 'c';
        break;
    case INFO_INT: fmt_str[0] = 'd';
        break; 
    case INFO_UINT: fmt_str[0] = 'u';
        break;
    case INFO_FLOAT: fmt_str[0] = 'f';
        break;
    case INFO_DOUBLE: fmt_str[0] = 'D';
        break;
    case INFO_LIST: fmt_str[0] = 1;
        break;
    case INFO_ARRAY: fmt_str[0] = 2;
        break;
    case INFO_POINTER: fmt_str[0] = 3;
        break;
    }
}

// Print a list
void print_list( head_t *head )
{
    unsigned    count = 0;
    node_t     *temp_ptr;
    char        fmt_str[2] = {0};

    // traverse the list from the list head
    if( head == NULL || head->len == 0 ) {
        printf("Empty list.\n");
        return;
    }
    else {
        temp_ptr = head->first;
    }
    
    printf("*-- ");
    while( count < head->len ) {
        get_fmt_str( fmt_str, temp_ptr->data.info_type);
        if( fmt_str[0] == 1 ) 
            print_list(temp_ptr->data.info.info_list);
        //else if( fmt_str[0] == 2 ) 
        //    print_array(temp_ptr->data);
        //else if( fmt_str[0] == 3 ) 
        //    print_ptr(temp_ptr->data);
        else if( fmt_str[0] == 'c')
            printf("%c, ", temp_ptr->data.info.info_char);
        else if( fmt_str[0] == 'd')
            printf("%d, ", temp_ptr->data.info.info_int);
        else if( fmt_str[0] == 'u')
            printf("%u, ", temp_ptr->data.info.info_uint);
        else if( fmt_str[0] == 'f')
            printf("%f, ", temp_ptr->data.info.info_float);
        else if( fmt_str[0] == 'D')
            printf("%f, ", temp_ptr->data.info.info_double);
        temp_ptr = temp_ptr->next;
        count++;
    }
    if( temp_ptr == NULL )
        printf("NULL--*\n");
    else
        printf("@ \n");
}

// Slice a list
void slice_list( head_t *head )
{
    return;
}

// Reverse a linked list using delete and insert
void reverse_list( head_t *head )
{
    head_t temp_head;
    node_t *temp_node = NULL;

    assert( head!= NULL );
    
    temp_head.first = NULL;
    temp_head.last = NULL;
    temp_head.len = 0;
    
    while( (temp_node = remove_fromfront( head )) != NULL ) {
        insert_atfront( &temp_head, temp_node );
    }
    head->first = temp_head.first;
    head->last = temp_head.last;
    head->len = temp_head.len;

}

// Reverse a linked list, iteratively
void reverse_list_iter( head_t *head )
{
    node_t *prevNode=NULL, *currNode=NULL, *nextNode=NULL;
    
    assert(head!=NULL);
    // return if nothing to reverse (list is empty or only one elemeent)
    if( head->first==NULL || head->first == head->last ) return;

    head->last = head->first;
    currNode = head->first;
    nextNode = currNode->next;
    currNode->next = prevNode;
    while(nextNode!=NULL) {
        head->first = nextNode;
        prevNode = currNode;
        currNode = nextNode;
        nextNode = currNode->next;
        currNode->next = prevNode;
    }

}

// Reverse a linked list, recursively
void reverse_list_recur( head_t *head )
{
    node_t *first_node=NULL;
    
    assert(head!=NULL);
    // return if nothing to reverse (list is empty or only one elemeent)
    if( head->first==NULL || head->first == head->last ) return;

    first_node = head->first;
    head->first = head->first->next;
    reverse_list_recur( head );
    head->last = head->last->next = first_node;
    first_node->next = NULL;

}

// Concatanate two lists: List1 = List1+List2, no separate header for list2 affter concat
void cat_list( head_t *head1, head_t *head2)
{
    assert( head1 != NULL || head2 != NULL );
    if( head2 == NULL || head2->last == NULL )
        return;
    else if( head1 == NULL || head1->last == NULL ) {
        *head1 = *head2;
        return;
    }
    head1->last->next = head2->first;
    head1->last = head2->last;
    head1->len += head2->len;
    init_list( head2 );
}

// Copy a list between [start,stop), stop not included
// e.g. to copy whole list, pass start=1, and stop=head->len+1
void copy_list1( const head_t *head, head_t *copy_head, size_t start, size_t stop )
{
	
}

// Copy a list
void copy_list( const head_t *head, head_t *copy_head )
{
    node_t *inode = NULL, *new_node = NULL, *prev_node = NULL;
    
    assert(head!=NULL && copy_head!=NULL);

    memcpy(copy_head, head, sizeof(head_t));
    
    for( inode = head->first; inode != NULL; inode = inode->next ) {
        new_node = malloc(sizeof(*new_node));
        if( new_node == NULL ) {
            printf("ERR1:Out of memory\n");
            return;
        }
        if( inode == head->first )
            copy_head->first = new_node;
        else
            prev_node->next = new_node;
        memcpy(&new_node->data, &inode->data, sizeof(data_t));
        new_node->next = NULL;
        prev_node = new_node;
    }

}

// Copy a list, fast
void copy_list_fast( const head_t *head, head_t *copy_head )
{
    node_t *inode = NULL;
    node_t *bulk_list = NULL;
    int     i = 0;

    assert(head!=NULL && copy_head!=NULL);

    memcpy(copy_head, head, sizeof(head_t));

    bulk_list = malloc(head->len * sizeof(*bulk_list));
    if( bulk_list == NULL ) {
        printf("ERR2:Out of memory\n");
        return;
    }
    copy_head->first = bulk_list;

    i = 0;
    for( inode = head->first; inode != NULL; inode = inode->next ) {
        bulk_list[i] = *inode;
        if( i<head->len-1 ) 
            bulk_list[i].next = &bulk_list[i+1];
        else
            bulk_list[i].next = NULL;
        i++;
    }
    copy_head->last = &bulk_list[i-1];
    copy_head->len = i;

}


// Detect a cycle in a list
bool detect_cycle( const head_t *head, size_t *start_pos, size_t *cyc_len )
{
    node_t *slow=NULL, *fast=NULL;
    assert( head!= NULL && start_pos !=NULL && cyc_len!=NULL );
    if( head->first == NULL )
        return false;
    
    slow = fast = head->first;
    
    // detect cycle
    do {
        slow = slow->next;
        fast = fast->next;
        if( fast==NULL ) 
            return false;
        else
            fast = fast->next;
        if( fast==NULL ) 
            return false;
    } while( slow!=fast );
    
    // find start position of cycle node
    *start_pos = 1;
    slow = head->first;
    do {
        slow = slow->next;
        fast = fast->next;
        (*start_pos)++;
    } while( slow!=fast );
    
    // find cycle len
    *cyc_len = 0;
    do {
        fast = fast->next;
        (*cyc_len)++;
    } while( slow!=fast );
    
    return true;
}

// Find minimum value in a list, return NULL if list is empty
node_t *find_min( head_t *head)
{
    node_t *inode=NULL, *min_node=NULL;
    int      retval = 0;
    
    assert( head!= NULL );

    for( inode=min_node=head->first; inode!=NULL; inode=inode->next ) {
        if( cmp_fn( &inode->data, &min_node->data, &retval) == false)
            return NULL;
        if( retval < 0 )
            min_node = inode;
    }
    return min_node;
}

// Find maximum value in a list, return NULL if list is empty
node_t *find_max( head_t *head)
{
    node_t *inode=NULL, *max_node=NULL;
    int      retval = 0;
    
    assert( head!= NULL );
    if( head->first == NULL )
        return NULL;
    
    for( inode=max_node=head->first; inode!=NULL; inode=inode->next ) {
        if( cmp_fn( &inode->data, &max_node->data, &retval) == false)
            return NULL;
        if( retval > 0 )
            max_node = inode;
    }
    return max_node;
}

// Place a node in a list in sorted order (inc order=0, dec order = 1)
void insert_inorder( head_t *head, node_t *anode, int order )
{
    node_t *inode=NULL, *prevnode=NULL, *temp=NULL;
    int     retval = 0;
    bool    cmp_result = false;
    
    assert( head!= NULL );
    if( anode == NULL )
        return;

    for( inode=head->first; inode!=NULL; inode=inode->next ) {
        if( cmp_fn( &anode->data, &inode->data, &retval ) == false )
            return;
        cmp_result = (order==0)? (retval<0): (retval>0);
        if( cmp_result )
            break;
        prevnode = inode;
    }
    // insert at front (including into an empty list)
    if( prevnode == NULL ) {
        if( head->first == NULL ) 
            head->last = anode;
        temp = head->first;
        head->first = anode;
        anode->next = temp;
    }
    // insert after prevnode (including at end)
    else {
        prevnode->next = anode;
        anode->next = inode;
        if( inode == NULL )
            head->last = anode;
    }
    head->len++;
}

// Sort a list using insertion sort
void insert_sort_list( head_t *head, int order )
{
    // pop items from given list and insert in order in a new list
    head_t   new_head;
    node_t  *temp_node = NULL;
    
    assert(head!=NULL);
    if( head->first == NULL || head->first->next == NULL ) 
        return;
    
    init_list( &new_head );
    while( (temp_node=remove_fromfront(head)) != NULL ) {
        insert_inorder( &new_head, temp_node, order);
    }
    head->first = new_head.first;
    head->last = new_head.last;
    head->len = new_head.len;
}

// Break an input list at pos p into two sublists left and right
void split_list_at( head_t *head_in, size_t pos, head_t *head_l, head_t *head_r) 
{
	
}

// Split an input list into two sublists with odd and even pos nodes
void split_alternate( head_t *head_in, head_t *head_o, head_t *head_e) 
{
    node_t   *move_ptr = NULL;
    head_t   *head_to = NULL;
    assert(head_in!=NULL && head_o!=NULL && head_e!=NULL);
    
    head_to = head_o;
    while( (move_ptr = remove_fromfront( head_in )) != NULL ) {
        insert_atend( head_to, move_ptr );
        if( head_to == head_o )
            head_to = head_e;
        else
            head_to = head_o;
    }
}

// Break an input list into two sublists with first half and second half
void split_list_half( head_t *head_in, head_t *head_f, head_t *head_b) 
{
    node_t *slow=NULL, *fast=NULL;
    assert(head_in!=NULL && head_f!=NULL && head_b!=NULL);
    
    init_list(head_f);
    init_list(head_b);
    
    slow = head_in->first;
    if( slow==NULL ) { // empty list
        return;
    }
    else if( slow->next  == NULL ) { // one element list
        head_f->first = head_f->last = slow;
        head_f->len = 1;
        return;
    }
    
    fast = slow->next;
    head_f->len = 1;
    do {
        fast = fast->next;
        head_b->len = head_f->len;
        if( fast==NULL ) {
            break; // even number of nodes
        }
        else { 
            slow = slow->next;
            head_f->len++;
            fast = fast->next; 
        }
    } while( fast!=NULL );
    
    // slow points to the last node of the front half
    if( slow!=NULL ) {
        head_b->first = slow->next;
        slow->next = NULL;
    }
    head_b->last = head_in->last;
    head_f->first = head_in->first;
    head_f->last = slow;
    init_list(head_in);
    
}

// Merge two lists into one list by taking nodes from eahc list alternatively
void merge_list_alternate( head_t *head1, head_t *head2, head_t *head_out)
{
    node_t   *move_ptr = NULL;
    head_t   *head_from = NULL;
    assert(head_out!=NULL && head1!=NULL && head2!=NULL);
    
    head_from = head1;
    while( (move_ptr = remove_fromfront( head_from )) != NULL ) {
        insert_atend( head_out, move_ptr );
        if( head_from == head1 )
            head_from = head2;
        else
            head_from = head1;
    }
    if( head_from == head1 )
        head_from = head2;
    else
        head_from = head1;
    while( (move_ptr = remove_fromfront( head_from )) != NULL ) {
        insert_atend( head_out, move_ptr );
    }
}

// Compare first node of list1 with the first node of list 2 and return ptr to lesser/bigger node
node_t *compare_node( head_t *head1, head_t *head2, int order) 
{
    data_t   *data1=NULL, *data2=NULL;
    int       retval = 0;
    bool      cmp_result = false;
    node_t   *retnode = NULL;
    head_t   *head_from=NULL;
    
    assert(head1!=NULL && head2!=NULL);
    
    data1 = check_at( head1, 1 );
    data2 = check_at( head2, 1 );
    if( data1!=NULL && data2!=NULL ) {
        if( cmp_fn( data1, data2, &retval )== false )
            return NULL;
        cmp_result = (order==0)? (retval<=0) : (retval>=0);
        head_from = cmp_result? head1: head2;
    }
    else if( data1==NULL ) 
        head_from = head2;
    else
        head_from = head1;
    
    retnode = remove_fromfront( head_from );
    
    return retnode;

}

// Merge two ordered list into one ordered list
void merge_list_inorder( head_t *head1, head_t *head2, head_t *head_out, int order)
{
    node_t   *move_ptr = NULL;
        
    assert(head1!=NULL && head2!=NULL);
    init_list( head_out );
    
    while( head1->first!=NULL && head2->first!=NULL ) {
        move_ptr = compare_node( head1, head2, order );
        insert_atend( head_out, move_ptr );
    }
    if( head1->first==NULL )
        cat_list( head_out, head2 );
    else
        cat_list( head_out, head1 );
}

// Sort a list using merge sort, using recursion
void merge_sort_list( head_t *head, int order )
{
    head_t head_left, head_right;
    assert( head!=NULL );
    if( head->first == NULL )
        return;
    if( head->first == head->last )
        return;
    
    init_list( &head_left );
    init_list( &head_right );
    
    split_list_half( head, &head_left, &head_right );
    
    merge_sort_list( &head_left, order );
    merge_sort_list( &head_right, order );
    merge_list_inorder( &head_left, &head_right, head, order );
    
}

// Check if given list is sorted or not
bool is_list_sorted( const head_t *head, int order ) 
{
    node_t *inode=NULL, *prevnode=NULL;
    int     retval = 0;
    bool    cmp_result = false;

    assert( head!=NULL );
    
    if( head->first == NULL || head->first == head->last )
        return true;
    
    prevnode = head->first;
    for( inode=prevnode->next; inode!=NULL; inode=inode->next ) {
        if( cmp_fn( &prevnode->data, &inode->data, &retval ) == false )
            return false;
        cmp_result = (order==0)? (retval>0):(retval<0);
        if( cmp_result ) 
            return false;
        prevnode = inode;
    }
    return true;
}

// Remove duplicate nodes in a sorted list
void unique_list( head_t *head, head_t *head_dup )
{
    node_t *prev_node=NULL, *inode=NULL, *dup_node=NULL;
    size_t  pos=0;
    int     retval = 0;
    
    assert( head!=NULL && head_dup!=NULL );
    if( head->first == NULL )
        return;
    if( head->first == head->last )
        return;
    init_list( head_dup );
    prev_node = head->first;
    inode = prev_node->next; 
    pos = 2;
    while( inode!=NULL ) {
        if( cmp_fn(&inode->data, &prev_node->data, &retval) == false )
            return;
        if( retval==0 ) { //inode same as prev_node
            dup_node = remove_at( head, pos);
            insert_atend( head_dup, dup_node );
            inode = prev_node->next;
        }
        else {
            prev_node = inode;
            inode = inode->next;
            pos++;
        }
    }
    
}

// Union and Intersection of two sorted lists, results are sorted & unique as well
size_t union_intersect_list( const head_t *head1, const head_t *head2, head_t *head_u, head_t *head_i, int order )
{
    size_t   com_count = 0; // number of common nodes
    head_t  head1_copy, head2_copy, head1_dup, head2_dup;
    node_t  *move_ptr=NULL, *prev_move_ptr=NULL;
    bool     match = false;
    int      retval = 0;

    assert( head1!=NULL && head2!=NULL && head_u!=NULL && head_i!=NULL );
    
    // init all intermediate and ouput list headers for a clean start
    init_list( &head1_copy );
    init_list( &head1_dup );
    init_list( &head2_copy );
    init_list( &head2_dup );
    init_list( head_u );
    init_list( head_i );

    // remove duplicates as they would not be there in union or intersect outputs
    copy_list( head1, &head1_copy );
    copy_list( head2, &head2_copy );
    unique_list( &head1_copy, &head1_dup );
    unique_list( &head2_copy, &head2_dup );
    // free memory not needed anymore
    free_list(&head1_dup);
    free_list(&head2_dup);
    
    // take care of empty lists as inputs
    if( head1_copy.first==NULL && head2_copy.first==NULL ) {
        return com_count;
    }

    // compare the front nodes of two lists and insert them in 
    // union list if they are not matching with prev inserted node
    // else insert it to the intersection list
    move_ptr = compare_node( &head1_copy, &head2_copy, order );
    insert_atend( head_u, move_ptr );
    prev_move_ptr = move_ptr;

    while( head1_copy.first!=NULL || head2_copy.first!=NULL ) {
        move_ptr = compare_node( &head1_copy, &head2_copy, order );
        if( cmp_fn( &move_ptr->data, &prev_move_ptr->data, &retval) == false ) {
            free_list(&head1_copy);
            free_list(&head2_copy);
            return 0;
        }
        if( retval == 0 ) {
            if( match == false ) {
                insert_atend( head_i, move_ptr );
                match = true;
            }
            com_count++;
        }
        else if( retval != 0 ) {
            insert_atend( head_u, move_ptr );
            match = false;
            prev_move_ptr = move_ptr;
        }
    }

    return com_count;
    
}






