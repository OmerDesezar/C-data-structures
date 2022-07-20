/*
    team: OL125-126    
    version: 1.1
    date: 25/04/2022
*/
#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include <stdint.h> /* uint64_t */
#include <stddef.h> /* size_t */

typedef uint64_t bitarray_t;

/* DESCRIPTION:
 * This function set all bits to 1
 *
 * PARAMS:
 * arr - bitarray to set bits in
 *
 * RETURN:
 * bitarray with all bits set
 */
bitarray_t BitArraySetAll(bitarray_t arr);


/* DESCRIPTION:
 * This function set one bit to 1 at given index
 * Index must be in range from 0 to 63
 * Out of range index will result in undefined behavior
 *
 * PARAMS:
 * arr     - bitarray to set bit in
 * index   - index of the bit
 *
 * RETURN:
 * bitarray with set bit on
 */
bitarray_t BitArraySetOn(bitarray_t arr, size_t index);



/* DESCRIPTION:
 * This function returns the value of bit by index
 * Index must be in range from 0 to 63
 * Out of range index will result in undefined behavior
 *
 * PARAMS:
 * arr     - bitarray to get value of bit from
 * index   - index of the bit to get value
 *
 * RETURN:
 * value of bit in a given index (0 or 1)
 */
int BitArrayGetVal(bitarray_t arr, size_t index);



/* DESCRIPTION:
 * This function rotate the bits n times to the right
 *
 * PARAMS:
 * arr                - bitarray to totate
 * num_of_rotations   - n times of rotations
 *
 * RETURN:
 * rotated bitarray
 */
bitarray_t BitArrayRotR(bitarray_t arr, size_t num_of_rotations);



/* DESCRIPTION:
 * This function count all the bits that are set
 *
 * PARAMS:
 * arr - bitarray to calculate set on bits
 * 
 * RETURN:
 * number of bits on in a given array
 */
size_t BitArrayCountOn(bitarray_t arr);
size_t BitArrayCountOnNoLoop(bitarray_t arr);
size_t BitArrayCountOnLUT(bitarray_t arr);


/* DESCRIPTION:
 * This function reset all the bits
 *
 * PARAMS:
 * arr - bitarray to reset
 * 
 * RETURN:
 * resetted bitarray 
 */
bitarray_t BitArrayResetAll(bitarray_t arr);



/* DESCRIPTION:
 * This function set one of the bits to 0
 * Index must be in range from 0 to 63
 * Out of range index will result in undefined behavior
 *
 * PARAMS:
 * arr     - bitarray to modify
 * index   - index of the bit to set off
 *
 * RETURN:
 * bitarray with specified bit off
 */
bitarray_t BitArraySetOff(bitarray_t arr, size_t index);



/* DESCRIPTION:
 * This function flip one of the bits in array
 * Index must be in range from 0 to 63
 * Out of range index will result in undefined behavior
 *
 * PARAMS:
 * arr      - bitarray to modify
 * index    - index of the bit
 *
 * RETURN:
 * bitarray with specidied bit flipped
 */
bitarray_t BitArrayFlip(bitarray_t arr, size_t index);



/* DESCRIPTION:
 * This function rotate the bits n times to the left
 *
 * PARAMS:
 * arr                - bitarray to totate
 * num_of_rotations   - n times of rotations
 *
 * RETURN:
 * rotated bitarray
 */
bitarray_t BitArrayRotL(bitarray_t arr, size_t num_of_rotations);




/* DESCRIPTION:
 * This function count all the bits that are off
 *
 * PARAMS:
 * arr - bitarray to calculate off bits
 * 
 * RETURN:
 * number of bits off in a given array
 */
size_t BitArrayCountOff(bitarray_t arr);




/* DESCRIPTION:
 * This function returns a string of the bits 
 *
 * PARAMS:
 * arr           - bitarray to turn into string
 * to_write_into - string to write into
 * 
 * RETURN:
 * pointer to string after writing into it
 */
char *BitArrayToString(bitarray_t arr, char *to_write_into);



/* DESCRIPTION:
 * This function set one bit to the requested value 
 * Index must be in range from 0 to 63
 * Out of range index will result in undefined behavior
 *
 * PARAMS:
 * arr   - bitarray to change
 * index - index of the bit
 * value - the requested value
 *
 * RETURN:
 * the bitarray with the changed bit
 */
bitarray_t BitArraySetBit(bitarray_t arr,size_t index, int value);



/* DESCRIPTION:
 * This function mirrors the entire bitarray
 *
 * PARAMS:
 * arr - the bitarray to mirror
 *
 * RETURN:
 * mirrored bitarray
 */
bitarray_t BitArrayMirror(bitarray_t arr);
bitarray_t BitArrayMirrorNoLoop(bitarray_t arr);
bitarray_t BitArrayMirrorLUT(bitarray_t arr);

#endif /* __BITARRAY_H__ */
