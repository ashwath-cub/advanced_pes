#include<stdlib.h>
#include<stdio.h>
#include<syslog.h>
#include<inttypes.h>


#include"circ_buff.h" 

#define BASIC_BUFF_SIZE   20
#define TOTAL_TESTS       10
#define SIZE_LOWER_LIMIT  -50
#define SIZE_UPPER_LIMIT  100

FILE * fp1;
void get_buff_state(CIRC_BUFF* cb)
{
    int fprintf_return;
    
    fprintf_return=fprintf(fp1, "Buffer Parameters:\nHead:%ld, Tail:%ld\ntotal_size:%d, size_occupied:%d\nHeap address:%p\n", cb->head-cb->base, cb->tail-cb->base, cb->total_size, cb->size_occupied, cb->base);
    
    if(fprintf_return<0)
    {
         printf("fprintf failed");
	 exit(-1); 
    }
}

void collect_state(circ_buff_code cb_code)
{
    switch(cb_code)
    {
         case CIRC_BUFF_SUCCESS:
              fprintf(fp1, "status: CIRC_BUFF_SUCCESS\n\n");
	      break;
         case CIRC_BUFF_NULL_PTR:
	      fprintf(fp1, "status: CIRC_BUFF_NULL_PTR\n\n");
	      break;
         case CIRC_BUFF_MALLOC_FAIL:
	      fprintf(fp1, "status: CIRC_BUFF_MALLOC_FAIL\n\n");
	      break;
         case CIRC_BUFF_BAD_DATA:
	      fprintf(fp1, "status: CIRC_BUFF_BAD_DATA\n\n");
	      break;
         case CIRC_BUFF_EMPTY:
	      fprintf(fp1, "status: CIRC_BUFF_EMPTY\n\n");
	      break;
         case CIRC_BUFF_FULL:
	      fprintf(fp1, "status: CIRC_BUFF_FULL\n\n");
	      break;
	 default:
	      break;
    }	    
    return;

}

int circ_buff_init_test()
{
    
    circ_buff_code cb_code;
    int index, count=0;
    CIRC_BUFF cb_new[TOTAL_TESTS];
    CIRC_BUFF* cb_ptr=cb_new;
    CIRC_BUFF** cb=&cb_ptr;

    int fprint_return;    
    
    fp1=fopen("test_results.vim", "w");
    
    if(fp1==NULL)
    {   
	printf("fopen failed\n\n");
        return 0;
    }	
    
    for(index=SIZE_LOWER_LIMIT; index<SIZE_UPPER_LIMIT; index++)
    {
         cb_code= circ_buff_init(&cb_new[count], index);
         
	 fprint_return=fprintf(fp1, "test case:%d\nAttempt at initializing a new buffer at:%p\n", count, &cb_new);
         
	 if(fprint_return<0)
	 {
	     printf("fprintf failed");
	     return 0;
	 }	 
	 
	 get_buff_state(&cb_new[count]); 
	 collect_state(cb_code);	 
         count++;
    }   
    fclose(fp1);
    return 0;
}
int buffer_contents(CIRC_BUFF* cb)
{
    int total_size= cb->total_size, index, head=cb->head-cb->base, tail=cb->tail-cb->base;
    
    fprintf(fp1, "Region:\t");
    for(index=0; index<total_size; index++)
         fprintf(fp1,"%"PRIu8"\t",*(cb->base+index));	    
    fprintf(fp1, "Buffer:\t");
    if(head>tail)
    {
         for(index=0; index<tail; index++)
	      fprintf(fp1, "%"PRIu8"\t", *(cb->base+index));
         for(index=tail; index<head; index++){
	      fprintf(fp1, "*\t");
	 }
	 for(index=head; index<total_size; index++){
	      fprintf(fp1, "%"PRIu8"\t", *(cb->base+index));
	 }
    }
    else{
         
	 for(index=0; index<head; index++){
	      fprintf(fp1, "*\t");
	 }
         
	 for(index=head; index<tail; index++){
	      fprintf(fp1, "%"PRIu8"\t", *(cb->base+index));
	 }

	 for(index=tail; index<total_size; index++){
	      fprintf(fp1, "*\t");
	 }     

    }    
    fprintf(fp1,"\nIndex:\t");
    for(index=0; index<total_size; index++)
         fprintf(fp1,"%d\t",index);	    
    fprintf(fp1,"\n\n");
    return 0;
}

int circ_buff_read_write_test()
{
    void** cb=(void**)malloc(sizeof(void*));
    
    circ_buff_code cb_code;
    int index;
    int writes, reads, writes_index, reads_index;
    uint32_t data_written, data_read;

    if(fp1==NULL)
    {   
	printf("fopen failed\n\n");
        return 0;
    }	
    
    
    circ_buff_init((CIRC_BUFF**)cb, BASIC_BUFF_SIZE);
    
    fprintf(fp1, "Before the first write:\n");
    get_buff_state(cb);   
    buffer_contents(cb); 

    for(index=0; index<TOTAL_TESTS; index++) 
    {
         writes=rand()%TOTAL_TESTS;
         fprintf(fp1, "Initiating %d writes\n\n", writes);

	 for(writes_index=0; writes_index<writes; writes_index++)
	 {
	      data_written=(uint8_t)(rand()%255);
	      cb_code=circ_buff_write(*cb, data_written);       
	      fprintf(fp1, "Test case: %d, After write: %d\n", index+1, writes_index+1);
	      buffer_contents(&cb);
	      get_buff_state(&cb); 
	      collect_state(cb_code);
	 }

         reads=(rand()%TOTAL_TESTS);

         fprintf(fp1, "Initiating %d reads\n\n", reads);

	 for(reads_index=0; reads_index<reads; reads_index++)
	 {
	      cb_code=circ_buff_read(&cb, &data_read);       
	      
	      fprintf(fp1, "Test case: %d, After read: %d\n", index+1, reads_index+1);
	      fprintf(fp1, "data read:%"PRIu8"\n",data_read);
	      
	      buffer_contents(&cb);
	      get_buff_state(&cb); 
	      collect_state(cb_code);
	 }	    
    }

    return 0;
}	

	

int main()
{
    fp1=fopen("test_results_read_write.vim", "w");
    circ_buff_read_write_test(); 
    return 0;
}

