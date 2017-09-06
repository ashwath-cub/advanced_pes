/*Declaring all functions which are defined in data.c*/
#include<stdint.h>


typedef enum {CIRC_BUFF_SUCCESS, CIRC_BUFF_NULL_PTR, CIRC_BUFF_MALLOC_FAIL, CIRC_BUFF_BAD_DATA, CIRC_BUFF_EMPTY, CIRC_BUFF_FULL, CIRC_BUFF_CAN_WRITE, CIRC_BUFF_CAN_READ} circ_buff_code;


/*								                
 * Structure:    circ_buff 
 * -----------------------------------------------------------------------------
 * Description:  A circular buffer structure that tracks the head, the tail, 
 *               the total size and the current size of the circular buffer.
 *           
 * Usage:        Use regular structure syntax to access any of the members of 
 *               this structure       
 * ----------------------------------------------------------------------------
 */
typedef struct circ_buff_tag
{
    uint32_t *base;
    uint32_t *head;
    uint32_t *tail;
    uint32_t  total_size;
    uint32_t  size_occupied;
}CIRC_BUFF;

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
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               successfully.  
 * ----------------------------------------------------------------------------
 */
circ_buff_code circ_buff_init(CIRC_BUFF* circ_buff_pointer, int16_t size);

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
circ_buff_code circ_buff_destroy(CIRC_BUFF* circ_buff_pointer);

/*								                
 * Function:     circ_buff_write(CIRC_BUFF* circ_buff_ptr, uint8_t data)
 * -----------------------------------------------------------------------------
 * Description:  Writes data to the circular buffer- circ_buff_ptr.
 *               
 * Usage:        Pass a pointer to the circular buffer, the data that needs to 
 *               be written in that order.
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
 *               successfully.   
 * ----------------------------------------------------------------------------
 */
circ_buff_code circ_buff_write(CIRC_BUFF* circ_buff_pointer, uint32_t data);


/*								                
 * Function:     circ_buff_read(CIRC_BUFF* circ_buff_pointer, uint32_t* data)
 * -----------------------------------------------------------------------------
 * Description:  Returns data from the circular buffer pointed by circ_buff_ptr, 
 *               based on the current head position in the buffer in the *data
 *               pointer.
 *               
 * Usage:        Pass a pointer to the circular buffer, a pointer to uint8_t 
 *               in that order. The pointer to uint32_t will contain the data
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
circ_buff_code circ_buff_read(CIRC_BUFF* circ_buff_pointer, uint32_t* data);

/*								                
 * Function:     circ_buff_size(CIRC_BUFF* circ_buff_pointer, uint32_t* size)
 * -----------------------------------------------------------------------------
 * Description:  Returns the current size of the buffer in the size pointer
 *               provided as an argument.
 *               
 * Usage:        Pass a pointer to the circular buffer, a pointer to a uint32_t 
 *               type in that order. The pointer to the uint32_t type will 
 *               contain the size occupied in buffer memory
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
circ_buff_code circ_buff_size(CIRC_BUFF* circ_buff_pointer, uint32_t* size);

circ_buff_code if_circ_buff_full(CIRC_BUFF* circ_buff_pointer);

circ_buff_code if_circ_buff_empty(CIRC_BUFF* circ_buff_pointer);
