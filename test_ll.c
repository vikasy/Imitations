#include <stdio.h>
#include "linked_list.h"

void create_list( head_t *head, int *datain, int len );

int main(void) 
{
    printf("Basic Test:\n");
    {
        head_t head1;
        int    datain[] = {10, 11, 12, 13, 14, 15, 16, 17};
        init_list( &head1 );
        create_list(&head1, datain, 8);
        print_list( &head1 );
        free_list(&head1);
        print_list( &head1 );
    }
    
    printf("\nDetect Cycle Test:\n");
    {
        bool retval = false;
        size_t start_pos=0, cyc_len=0;
        head_t head1;
        int    datain[] = {10, 11, 12, 13, 14, 15, 16, 17};
        init_list( &head1 );
        print_list( &head1 );
        retval = detect_cycle( &head1, &start_pos, &cyc_len );
        printf("cycle or not=%d, start=%u, len=%u\n", retval, (unsigned)start_pos, (unsigned)cyc_len);
        create_list(&head1, datain, 8);
        print_list( &head1 );
        retval = detect_cycle( &head1, &start_pos, &cyc_len );
        printf("cycle or not=%d, start=%u, len=%u\n", retval, (unsigned)start_pos, (unsigned)cyc_len);
        //{10, 11, 12, 13, 14, 15, 16, 17};
        //          ^-------------------!
        head1.last->next = head1.first->next->next;
        print_list( &head1 );
        retval = detect_cycle( &head1, &start_pos, &cyc_len );
        printf("cycle or not=%d, start=%u, len=%u\n", retval, (unsigned)start_pos, (unsigned)cyc_len);
        free_list(&head1);
        print_list( &head1 );
    }
    
    printf("\nReversal Test:\n");
    {
        head_t head1;
        int    datain[] = {10, 11, 12, 13, 14, 15, 16, 17};
        init_list( &head1 );
        reverse_list( &head1 );
        print_list( &head1 );
        create_list(&head1, datain, 8);
        print_list( &head1 );
        reverse_list( &head1 );
        print_list( &head1 );
        reverse_list_iter( &head1 );
        print_list( &head1 );
        reverse_list_recur( &head1 );
        print_list( &head1 );
        free_list(&head1);
        print_list( &head1 );
    }
    
    printf("\nConcat Test:\n");
    {
        head_t head1, head2;
        int    datain[] = {10, 11, 12, 13, 14, 15, 16, 17};
        init_list( &head1 );
        init_list( &head2 );
        cat_list( &head1, &head2 );
        print_list( &head1 );
        print_list( &head2 );
        create_list(&head1, datain, 8);
        print_list( &head1 );
        cat_list( &head1, &head2 );
        print_list( &head1 );
        print_list( &head2 );
        create_list(&head2, datain, 4);
        print_list( &head2 );
        // catlist will make head1=head1+head2, head2 set to no list
        cat_list( &head1, &head2 );
        print_list( &head1 );
        print_list( &head2 );
        free_list(&head1);
        //free_list(&head2);
        print_list( &head1 );
        print_list( &head2 );
    }

    printf("\nCopy Test:\n");
    {
        head_t head1, head2;
        int    datain[] = {11, 12, 13, 14, 15, 16, 17, 18};
        init_list( &head1 );
        copy_list( &head1, &head2 );
        //copy_list_fast( &head1, &head2 );
        print_list( &head1 );
        print_list( &head2 );
        create_list(&head1, datain, 8);
        print_list( &head1 );
        copy_list( &head1, &head2 );
        //copy_list_fast( &head1, &head2 );
        print_list( &head2 );
        free_list( &head1 );
        print_list( &head1 );
        free_list( &head2 );
        //free( head2->first );
        //head2->first = head2->last = NULL;
        //head2->len = 0;
        print_list( &head2 );
    }

    printf("\nMinMax Test:\n");
    {
        head_t  head1;
        node_t *min=NULL, *max=NULL;
        int    datain[] = {19, 11, 22, 13, 44, 15, 16, 17};
        init_list( &head1 );
        max = find_max( &head1 );
        min = find_min( &head1 );
        if(min==NULL ||max==NULL)
            printf("Lists are empty\n");
        else
            printf("min=%d, max=%d\n",min->data.info.info_int,max->data.info.info_int);
        create_list(&head1, datain, 8);
        print_list( &head1 );
        max = find_max( &head1 );
        min = find_min( &head1 );
        if(min==NULL ||max==NULL)
            printf("ERR:null pointer\n");
        else
            printf("min=%d, max=%d\n",min->data.info.info_int,max->data.info.info_int);
        print_list( &head1 );
        free_list(&head1);
        print_list( &head1 );
    }
    
    printf("\nInsertion Sort Test:\n");
    {
        head_t  head1;
        data_t  d;
        node_t  *anode, *bnode;
        int    datain[] = {19, 11, 22, 13, -1, 44, 15, 16, 17, 0};
        init_list( &head1 );
        insert_sort_list( &head1, 0 );
        print_list( &head1 );
        create_list(&head1, datain, 10);
        print_list( &head1 );
        insert_sort_list( &head1, 0 );
        print_list( &head1 );
        insert_sort_list( &head1, 1 );
        print_list( &head1 );
        d.info_type = INFO_INT;
        d.info.info_int = -100;
        anode = get_node( &d );
        insert_inorder( &head1, anode, 1 );
        print_list( &head1 );
        d.info.info_int = 11;
        bnode = get_node( &d );
        insert_inorder( &head1, bnode, 1 );
        print_list( &head1 );
        free_list( &head1 );
        print_list( &head1 );
    }

    printf("\nList Splitting Test:\n");
    {
        head_t  head1, head2, head3, *head4;
        int     datain[] = {19, 11, 22, 13, -1, 44, 15, 16, 17, 0, 1};
        init_list( &head1 );
        init_list( &head2 );
        init_list( &head3 );
        split_alternate( &head1, &head2, &head3 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        head4 = (head_t *)malloc(sizeof(head_t));
        init_list( head4 );
        create_list(&head1, datain, 11);
        print_list( &head1 );
        split_alternate( &head1, &head2, &head3 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        cat_list( &head2, &head3 );
        print_list( &head2 );
        print_list( &head3 );
        copy_list( &head2, head4 );
        print_list( head4 );
        split_list_half( head4, &head2, &head3 );
        print_list( head4 );
        print_list( &head2 );
        print_list( &head3 );
        cat_list( &head2, &head3 );
        print_list( &head2 );
        print_list( &head3 );
        copy_list( &head2, head4 );
        print_list( head4 );
        free_list( head4 );
        free_list( &head2 );
        print_list( &head1 );
    }

    printf("\nList Merging Test:\n");
    {
        head_t  head1, head2, head3;
        int     datain[] = {19, 11, 22, 13, -1, 44, 15, 16, 17, 0, 1};
        init_list( &head1 );
        init_list( &head2 );
        init_list( &head3 );
        split_list_half( &head1, &head2, &head3 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        create_list(&head1, datain, 11);
        print_list( &head1 );
        insert_sort_list( &head1, 0 );
        print_list( &head1 );
        split_list_half( &head1, &head2, &head3 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        merge_list_inorder( &head2, &head3, &head1, 0 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        split_list_half( &head1, &head2, &head3 );
        merge_list_alternate( &head2, &head3, &head1);
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        cat_list( &head2, &head3 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        free_list( &head1 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
    }
    
    printf("\nMerge Sort Test:\n");
    {
        head_t  head1;
        data_t  d;
        node_t *anode, *bnode;
        bool    cmp_result;
        int    datain[] = {19, 11, 22, 13, -1, 44, 15, 16, 17, 0};
        init_list( &head1 );
        merge_sort_list( &head1, 0 );
        print_list( &head1 );
        cmp_result = is_list_sorted( &head1, 0);
        printf("Sorted=%d\n",cmp_result);
        create_list(&head1, datain, 10);
        print_list( &head1 );
        cmp_result = is_list_sorted( &head1, 1);
        printf("Sorted=%d\n",cmp_result);
        merge_sort_list( &head1, 0 );
        print_list( &head1 );
        cmp_result = is_list_sorted( &head1, 0);
        printf("Sorted=%d\n",cmp_result);
        merge_sort_list( &head1, 1 );
        print_list( &head1 );
        cmp_result = is_list_sorted( &head1, 1);
        printf("Sorted=%d\n",cmp_result);
        d.info_type = INFO_INT;
        d.info.info_int = -100;
        anode = get_node( &d );
        insert_inorder( &head1, anode, 1 );
        print_list( &head1 );
        d.info.info_int = 11;
        bnode = get_node( &d );
        insert_inorder( &head1, bnode, 1 );
        print_list( &head1 );
        cmp_result = is_list_sorted( &head1, 1);
        printf("Sorted=%d\n",cmp_result);
        free_list( &head1 );
        print_list( &head1 );
    }
    
    printf("\nUnique/Union/Intersect Test:\n");
    {
        head_t  head1, head2, head3, head4;
        bool    cmp_result;
        int     datain[] = {19, 11, 22, 13, 13, 44, 15, 19, 17, 13};
        int     datain2[] = {9, 11, 2, 13, 3, 44, 5};
        init_list( &head1 );
        init_list( &head2 );
        init_list( &head3 );
        init_list( &head4 );
        unique_list( &head1, &head2 );
        print_list( &head1 );
        print_list( &head2 );
        union_intersect_list( &head1, &head2, &head3, &head4, 0 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        print_list( &head4 );
        create_list(&head1, datain, 10);
        print_list( &head1 );
        merge_sort_list( &head1, 0 );
        print_list( &head1 );
        cmp_result = is_list_sorted( &head1, 0);
        printf("Sorted=%d\n",cmp_result);
        unique_list( &head1, &head2 );
        print_list( &head1 );
        print_list( &head2 );
        free_list(&head1);
        free_list(&head2);
        init_list( &head1 );
        init_list( &head2 );
        create_list(&head1, datain, 10);
        create_list(&head2, datain2, 7);
        merge_sort_list( &head1, 0 );
        cmp_result = is_list_sorted( &head1, 0);
        printf("Sorted=%d\n",cmp_result);
        cmp_result = is_list_sorted( &head2, 0);
        printf("Sorted=%d\n",cmp_result);
        merge_sort_list( &head2, 0 );
        print_list( &head1 );
        print_list( &head2 );
        union_intersect_list( &head1, &head2, &head3, &head4, 0 );
        print_list( &head1 );
        print_list( &head2 );
        print_list( &head3 );
        print_list( &head4 );
    }
    
    return 0;
}


void create_list( head_t *head, int *datain, int len )
{
    int     i;
    node_t *node_ptr;
    data_t  data_ptr;
    
    data_ptr.info_type = INFO_INT;
    for( i=0; i<len; ++i ) {
        data_ptr.info.info_int = datain[i];
        node_ptr = get_node(&data_ptr);
        insert_atend( head, node_ptr);
    }
    
}