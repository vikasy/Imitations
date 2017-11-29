/**********************************************************************
  Author: Vikas YADAV (vikasy@gmail.com)
  Filename: dynamic_malloc.c
  Topic: Implementaton of dynamic memory allocation using "first-fit" scheme

 Implements:
 void *my_malloc( size_t size);
 void  my_free( void *p );
 
 In reality program gets memory in heap from kernel via system call like 
 sbrk(size_t size) system call in unix-like, however, here for simulation 
 purpose we use my_sbrk(size_t newsize) function.

 Mem allocation is done from a big blob of contingous memory of 100MB. 
 Each allocated memory size is sum of requested memory size plus overhead. 
 Overhead consists of header info and extra memory due to minimum memory 
 size restriction and to keep total memory aligned to double word boundry.

 Freelist is a circular linked list arranged in increasing order of  
 starting memory address of free memory blocks. 

 The allocation uses "first-fit" policy, where the first available node 
 (one with memory size greater than or eequal to the requested size) in 
 freelist is used to allocate requested memory. 
 The search for the next fit block to meet requested size starts beyond 
 the most recent block position.The allocated memory has a minimum size, 
 thus if requested memory is less than minimum size, the  system will 
 allocate the minimum size, causing what is called internal memory 
 fragmentation.


***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MYHEAPSIZE    2000000         // 2MB
#define MAXALLOCS     120
#define BLOCKOVHEAD   16              // sizeof(node_t*)+sizeof(size_t)
#define MINALLOCSIZE  BLOCKOVHEAD + 8 // +sizeof(long long)
#define ALIGN         8               // 8 bytes =sizeof(long long)

typedef union {
    struct {
        struct node *next;        // pointer to the next free block
        size_t       size;        // size of the whole memory out of system
    } s;
    long long    align;
} header_t;

typedef struct node {
    header_t     header;
    void        *retaddress;  // the memory address returned to user
} node_t;

typedef struct head {
    struct node *first;
    struct node *last;
    struct node *curr;
    size_t       len;
} head_t;

static char     MYHEAP[MYHEAPSIZE];  // in reality this comes from OS via a syscall
static head_t   freelist;            // header for the circular linked list of free blocks
    
void *my_malloc( size_t sz);
void  my_free( void *p );
void  print_list( head_t *head );

int main( void )
{
    void    *alloclist[MAXALLOCS] = {0}; // list of allocated blocks
    size_t   reqsize = 0;
    int      i;
    node_t  *nodeptr;
    
    freelist.len = 1;
    freelist.first = freelist.last = freelist.curr = nodeptr = (node_t *)MYHEAP;
    
    nodeptr->header.s.size = (MYHEAPSIZE/sizeof(header_t))*sizeof(header_t); 
    nodeptr->header.s.next = nodeptr;
    nodeptr->retaddress = MYHEAP+sizeof(header_t);
    
    printf("(%p,%p)%u\n",freelist.first,nodeptr->retaddress, (unsigned)sizeof(header_t));

    srand (time(NULL));

    for(i=0; i<MAXALLOCS; ++i ) {
        reqsize = (size_t)rand();
        alloclist[i] = my_malloc(reqsize);
    }
    print_list( &freelist );
    for(i=0; i<MAXALLOCS; ++i ) {
        my_free(alloclist[i]);  
        alloclist[i] = 0;
    }
    print_list( &freelist );

    return 0;
}

// Allocate memory using first-fit algo
void *my_malloc( size_t sz )
{
    size_t    count = 0;
    node_t   *prevnode = NULL;
    size_t    allocsz = 0;;
    header_t *retadd = NULL;
    
    // total size = sz + overhead (due to quantiaztion of size in multiples of sizeof(header_t))
    //allocsz = ((sz + ALIGN - 1)/ALIGN + 1)*ALIGN;
    allocsz = (sz + ALIGN - 1) & ~(ALIGN-1);
    if( allocsz > MYHEAPSIZE) return NULL;
    // make sure not less than specific amount is allocated to minimize external frag
    if( allocsz < 2*sizeof(header_t)) allocsz = 2*sizeof(header_t);
    
    // find the first block of size greater than or equal to sz
    // start searching form the next to the recently allocated block
    while( count < freelist.len ) {
        prevnode = freelist.curr;
        freelist.curr = freelist.curr->header.s.next;
        if( freelist.curr->header.s.size == allocsz ) {
            // found a block, remove it from the list to provide for requested memory
            if( freelist.len == 1 ) {
                // special handling if only one node is present
                retadd = freelist.curr->retaddress;
                freelist.first = NULL;
                freelist.last = NULL;
                freelist.curr = NULL;
                freelist.len--;
                break;
            }
            else {
                retadd = freelist.curr->retaddress;
                if( freelist.curr == freelist.first ) {
                    freelist.first = freelist.curr->header.s.next;
                }
                else if( freelist.curr == freelist.last ) {
                    freelist.last = freelist.curr->header.s.next;
                }
                freelist.curr = prevnode->header.s.next = freelist.curr->header.s.next;
                freelist.len--;
                break;
            }
        }
        else if( freelist.curr->header.s.size > sz ) {
            // found a block, reduce it by taking off the tail end for required memory
            freelist.curr->header.s.size -= allocsz;
            retadd = (header_t *)((char*)freelist.curr + freelist.curr->header.s.size);
            retadd->s.size = allocsz;
            retadd = (header_t *)((char*)retadd + sizeof(header_t));
            break;
            
        }
        count++;
    }
    printf("reqsz=%u,allocsz=%u,add=%p\n",(unsigned)sz,(unsigned)allocsz,retadd);
    
    if( retadd == NULL ) {
        printf("OUT OF MEMORY\n");
        // or implement something like sbrk to get more memory
    }
    
    return (void *)retadd;
}

void my_free( void *p )
{
    size_t    pos = 0;
    node_t   *inode = NULL, *prevnode=NULL;
    header_t *pheader = NULL;

    if( p == NULL ) {
        printf("Null ptr to free!\n");
        return;
    }
    pheader = (header_t *)( (char*)p - sizeof(header_t) );
    if( pheader->s.size == 0 || pheader->s.size > MYHEAPSIZE ) return;

    static int i=0;
    printf("i=%d,totsz=%u,add2free=%p\n",i++,(unsigned)pheader->s.size,p);
    // Q1. where to place the freed mem block pointed by p
    // The freelist cirualr link list is maintained in increasing order of start address of each node
    // The newly freed mem block is placed in this list while maintaining this order.
    // 2. how to determine if it is adjacent to a free block on either side or both
    // 3. how to combine it with adjacent free blocks
    for( inode=freelist.first; pos<freelist.len; prevnode=inode, inode=inode->header.s.next ) {
        if( (char*)inode > (char*)pheader ) 
            break;
        pos++;
    }
    // pos (0-based) indicates the pos of the node bigger than size of p
    if( pos == freelist.len ) {
        // insert at the end, but first check if it can be combined with last node
        if( (char*)freelist.last + freelist.last->header.s.size == (char*)pheader ) {
            freelist.last->header.s.size += pheader->s.size;
        }
        else { // insert at end
            freelist.last->header.s.next = (node_t *)pheader;
            pheader->s.next = freelist.first;
            freelist.last = (node_t *)pheader;
            freelist.len++;
        }
    }
    else if( pos == 0) {
        // insert at the front, but first check if it can be combined with front node
        if( (char*)freelist.first == (char*)pheader + pheader->s.size ) {
            freelist.first->header.s.size += pheader->s.size;
            freelist.first = (node_t *)pheader;
        }
        else { // insert at front
            freelist.last->header.s.next = (node_t *)pheader;
            pheader->s.next = freelist.first;
            freelist.first = (node_t *)pheader;
            freelist.len++;
        }
    }
    else {
        // insert before pos in the middle (between prevnode and inode)
        // before that check if it can be combined with any of the adjacent blocks (or both maybe)
        if( (char*)prevnode + prevnode->header.s.size == (char*)pheader ) {    // combine with prev
            prevnode->header.s.size += pheader->s.size;   
            if( (char*)prevnode + prevnode->header.s.size == (char*)inode ) {  // combine with next as well
                prevnode->header.s.size += inode->header.s.size;
                prevnode->header.s.next = inode->header.s.next;
                if( freelist.last == inode ) 
                    freelist.last = inode->header.s.next;
                freelist.len--;
            }
        }
        else if( (char*)inode == (char*)pheader + pheader->s.size ) {     // combine with next only
            prevnode->header.s.next = (node_t *)pheader;
            pheader->s.next = inode->header.s.next;
            pheader->s.size += inode->header.s.size;
            if( freelist.last == inode ) 
                    freelist.last = (node_t *)pheader;
        }
        else { // insert between prevnode and inode
            prevnode->header.s.next = (node_t *)pheader;
            pheader->s.next = inode;
            freelist.len++;
        }
    }

}

// Print a list
void print_list( head_t *head )
{
    unsigned    count = 0;
    node_t     *temp_ptr=NULL;
    size_t      sz;
    void       *ptr;

    // traverse the list from the list head
    if( head == NULL || head->len == 0 ) {
        printf("Empty queue.\n");
        return;
    }
    else {
        temp_ptr = head->first;
    }
    
    printf("*<- ");
    while( count < head->len ) {
        sz = temp_ptr->header.s.size;
        ptr = temp_ptr->header.s.next;
        printf("[%u, %p]", (unsigned)sz, ptr);
        temp_ptr = temp_ptr->header.s.next;
        count++;
    }
    printf("NULL-<*\n");
    
}




