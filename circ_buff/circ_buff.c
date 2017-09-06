/* 
 * Author:       Ashwath Gundepally, CU ECEE
 * 
 * File:         circ_buff.c
 * 
 * Description:  Contains an implementation of a circular buffer
 *               that supports basic operations like write an item,
 *               read an item, find size, etc.
 *
 * */


#include "circ_buff.h"
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<inttypes.h>

#define fp1 stdout


/*								                
 * Function:     circ_buff_init(CIRC_BUFF* circ_buff_ptr, int16_t size)
 * -----------------------------------------------------------------------------
 * Description:  Assigns memory specified by 'size' to the circular buffer 
 *               structure pointed to by the pointer argument on the heap. 
 *               Also initialises various parameters to this buffer, like the 
 *               head, tail, total size, and size_occupied, etc.  
 *              
 *           
 * Usage:        Pass a pointer to the circular buffer struc which needs to be
 *               allocated memory on the heap, and an in16_t type specifying 
 *               the size in that order.
 * 
 * Returns:      Error codes:
 *               CIRC_BUFF_NULL_POINTER: The pointer passed is detected to be a 
 *               null. The function halts execution and returns w/o completion.   
 *                  
 *               CIRC_BUFF_BAD_DATA: The size parameter is less than or equal 
 *               to zero.
 *               
 *               CIRC_BUFF_MALLOC_FAIL: The call to malloc fails.
 *
 *               CIRC_BUFF_SUCCESS: The funcion returns successfully.
 */
circ_buff_code circ_buff_init(CIRC_BUFF** circ_buff_pointer, uint32_t size)
{
    //error handling
    if(circ_buff_pointer==NULL)                        //check if the pointer is NULL
         return CIRC_BUFF_NULL_PTR;   
    *(circ_buff_pointer)=(CIRC_BUFF*)malloc(sizeof(CIRC_BUFF));
    
    if((*circ_buff_pointer)==NULL)
         return CIRC_BUFF_MALLOC_FAIL;
    
    (*circ_buff_pointer)->base=(uint32_t*)malloc(size);    //access the buff pointer and allocate memory on the heap
    
    if((*circ_buff_pointer)->base==NULL)
         return CIRC_BUFF_MALLOC_FAIL;

    /*Initialise total and current size to the allocated memory*/
    (*circ_buff_pointer)->size_occupied=0;             
    (*circ_buff_pointer)->total_size=size;
    
    /*Initialise the head and tail positions to base*/
    (*circ_buff_pointer)->head=(*circ_buff_pointer)->base;                        
    (*circ_buff_pointer)->tail=(*circ_buff_pointer)->base;   
    
    return CIRC_BUFF_SUCCESS;                          //return successfully
}	


/*								                
 * Function:     circ_buff_destroy(CIRC_BUFF* circ_buff_ptr)
 * -----------------------------------------------------------------------------
 * Description:  De-allocates memory on the heap allocated to the circ_buffer_
 *               pointer.
 *               
 *              
 * Usage:        Pass a pointer to the circular buffer struc which needs to be
 *               de-allocated memory on the heap.
 * 
 * Returns:      Error codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               completely.   
 * ----------------------------------------------------------------------------
 */
circ_buff_code circ_buff_destroy(CIRC_BUFF* circ_buff_pointer)
{
    //basic pointer check; error handling	
    if(circ_buff_pointer==NULL)
	 return CIRC_BUFF_NULL_PTR;
    
    //free the memory of the buffer on the heap
    free(circ_buff_pointer->base);

    /*Reassign all the parameters to 0*/
    circ_buff_pointer->size_occupied=0;             
    circ_buff_pointer->total_size=0;
    
    /*assigning some random value that is not between 0 and size-1 signifies that the buffer is empty*/
    circ_buff_pointer->head=NULL;                        
    circ_buff_pointer->tail=NULL;   

    
    return CIRC_BUFF_SUCCESS; 
}

circ_buff_code if_circ_buff_full(CIRC_BUFF* circ_buff_pointer)
{
    //basic pointer check; error handling	
    if(circ_buff_pointer==NULL)
	 return CIRC_BUFF_NULL_PTR;
    
    uint32_t current_buff_size=circ_buff_pointer->size_occupied, total_buff_size= circ_buff_pointer->total_size;
    
    //check if the buffer is full
    if(current_buff_size ==total_buff_size)
	 return CIRC_BUFF_FULL;
    else
	 return CIRC_BUFF_CAN_WRITE; 
}


circ_buff_code if_circ_buff_empty(CIRC_BUFF* circ_buff_pointer)
{
    //basic pointer check; error handling	
    if(circ_buff_pointer==NULL)
	 return CIRC_BUFF_NULL_PTR;
    
    uint32_t current_buff_size=circ_buff_pointer->size_occupied;  //read current buffer size
    
    //check if the buffer is emptry
    if(current_buff_size ==0)
	 return CIRC_BUFF_EMPTY;
    else
	 return CIRC_BUFF_CAN_READ; 
}


/*								                
 * Name:         circ_buff_write(CIRC_BUFF* circ_buff_ptr, uint8_t data)
 * -----------------------------------------------------------------------------
 * Description:  Writes data to the circular buffer at circ_buff_ptr.
 *               
 * Working:      Writes at location tail+1 if there is space. Calculates space 
 *               first. Returns error if there is no space. Also updates tail 
 *               and the size_occupied upon a successful write.  
 * 
 * Returns:      Error codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               CIRC_BUFF_FULL: The buffer is currently full and thus new
 *               data can not be written to it.
 *
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               completely.   
 * ----------------------------------------------------------------------------
 */
circ_buff_code circ_buff_write(CIRC_BUFF* circ_buff_pointer, uint32_t data)
{
    //basic pointer check; error handling	
    if(circ_buff_pointer==NULL)
	 return CIRC_BUFF_NULL_PTR;

    circ_buff_code if_write_ok=if_circ_buff_full(circ_buff_pointer);
    
    if(if_write_ok!=CIRC_BUFF_CAN_WRITE)
	 return CIRC_BUFF_FULL;

    uint32_t total_buff_size= circ_buff_pointer->total_size;
    

    *(circ_buff_pointer->tail)=data;  //grab the tail and write to it
    
    if((circ_buff_pointer->tail-circ_buff_pointer->base)!=total_buff_size)
         circ_buff_pointer->tail++;           //update tail circularly
    else
	 circ_buff_pointer->tail=circ_buff_pointer->base;

    //update the size occupied by the buffer 
    circ_buff_pointer->size_occupied++;

    return CIRC_BUFF_SUCCESS;
}

/*								                
 * Function:     circ_buff_read(CIRC_BUFF* circ_buff_pointer, uint8_t* data)
 * -----------------------------------------------------------------------------
 * Description:  Returns data from the circular buffer pointed by circ_buff_ptr, 
 *               based on the current head position in the buffer in the *data
 *               pointer.
 *               
 * Usage:        Pass a pointer to the circular buffer, a pointer to uint8_t 
 *               in that order. The pointer to uint8_t will contain the data
 *               at the head of the circular buffer.
 *                
 * Returns:      Error codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *               
 *               CIRC_BUFF_EMPTY: The buffer is currently empty and thus can
 *               not return any data.
 *               
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               completely.   
 * ----------------------------------------------------------------------------
 */
circ_buff_code circ_buff_read(CIRC_BUFF* circ_buff_pointer, uint32_t* data)
{
    //basic pointer check; error handling	
    if(circ_buff_pointer==NULL||data==NULL)
	 return CIRC_BUFF_NULL_PTR;
    
    circ_buff_code if_read_ok=if_circ_buff_empty(circ_buff_pointer);     //get buffer status- find if data can be read
    
    if(if_read_ok!=CIRC_BUFF_CAN_READ)
	    return CIRC_BUFF_EMPTY;                      //the buffer is empty; nothing to read
    
    uint32_t total_buff_size= circ_buff_pointer->total_size;
    

    *data= *(circ_buff_pointer->head);  //assign the byte located at head to data and complete the read 

    //update head circularly
    if(circ_buff_pointer->head!=circ_buff_pointer->base)
         circ_buff_pointer->head--;           
    else
	 circ_buff_pointer->head=(circ_buff_pointer->base)+total_buff_size;



    //update the size occupied by the buffer
    circ_buff_pointer->size_occupied--;

    return CIRC_BUFF_SUCCESS;
}	

circ_buff_code dump(CIRC_BUFF* cb)
{
    uint32_t total_size= cb->total_size, index; 
    uint32_t head=cb->head-cb->base, tail=cb->tail-cb->base;
    
    fprintf(fp1, "Region:\t");
    for(index=0; index<total_size; index++)
         fprintf(fp1,"%"PRIu32"\t",*(cb->base+index));
    
    fprintf(fp1, "Buffer:\t");

    if(head>tail)
    {
         for(index=0; index<tail; index++)
              fprintf(fp1, "%"PRIu32"\t", *(cb->base+index));
         for(index=tail; index<head; index++){
              fprintf(fp1, "*\t");
         }
         for(index=head; index<total_size; index++){
              fprintf(fp1, "%"PRIu32"\t", *(cb->base+index));
         }
    }
    else{

         for(index=0; index<head; index++){
              fprintf(fp1, "*\t");
         }

         for(index=head; index<tail; index++){
              fprintf(fp1, "%"PRIu32"\t", *(cb->base+index));
         }

         for(index=tail; index<total_size; index++){
              fprintf(fp1, "*\t");
         }
    
    }    
    fprintf(fp1,"\nIndex:\t");
    for(index=0; index<total_size; index++)
         fprintf(fp1,"%d\t",index);
    fprintf(fp1,"\n\n");
    
    return CIRC_BUFF_SUCCESS;
}







































/*								                
 * Function:     circ_buff_size(CIRC_BUFF* circ_buff_pointer, uint8_t* size)
 * -----------------------------------------------------------------------------
 * Description:  Returns the current size of the buffer in the size pointer
 *               provided as an argument.
 *               
 * Usage:        Pass a pointer to the circular buffer, a pointer to uint8_t 
 *               in that order. The pointer to a uint8_t will contain the data
 *               at the head of the circular buffer.
 *               
 * Returns:      Error codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *               
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               completely.   
 * ----------------------------------------------------------------------------
 */
/*circ_buff_code circ_buff_size(CIRC_BUFF* circ_buff_pointer, uint16_t* size)
{
    //basic pointer check; error handling	
    if(circ_buff_pointer==NULL||size==NULL)
	 return CIRC_BUFF_NULL_PTR;
    

    uint16_t current_head=circ_buff_pointer->head, current_tail= circ_buff_pointer->tail, total_buff_size= circ_buff_pointer->total_size;
   */ 
    /* Case 1:  ------*************------
     *                ^           ^      
     *                |           |      
     *               head       tail   
     *         
     *          length=head-tail    
     *
     * Case 2: ********-----------********
     *                ^           ^      ^
     *                |           |      |
     *              tail        head  buffer-end 
     *     
     *     length=(total_size-head)+(total_size-tail)
     *
     */
/*    if(current_head>current_tail)
         *size=(total_buff_size-(current_head+1))+ (total_buff_size-(current_tail+1));
    else
	 *size=current_tail-current_head;
    
    
    return CIRC_BUFF_SUCCESS;
}
*/


