/*
 * Filename: timeCompareRev.s
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: defines the nameCompare funtion that is passed in as
 *              parameter for qsort() function used in the PA4 program.
 * Date: 11/27/18
 * Sources of Help: Piazza
 */

.syntax unified

.equ FP_OFFSET, 4
.equ PARAM_SPACE, 16
.equ P1_OFFSET, -8
.equ P2_OFFSET, -12

.text
.align 2
.global timeCompareRev

/*
 * Function name: timeCompareRev()
 * Function prototype: int timeCompareRev(cons void * p1, const void * p2);
 * Description: This funcion will compare the two time values from the 
 * two different structs, and will return -1,1, or 0 depending on how the 
 * modification time from the two structs differ
 * Parameters: p1 is a pointer to a struct
 * p2 is a pointer to a struct
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: 1, if mod time is older, 0 if same , -1 is mod time is newer
 * Registers Used: 
 *  r0 - time of first struct
 *  r1 - time of second struct
 *  r3 - the time offset.
 */

timeCompareRev:
    @ Save caller's registers on the stack
    push {fp, lr}

    add     fp, sp, FP_OFFSET
    sub     sp, sp, PARAM_SPACE
    ldr     r0, [r0]
    ldr     r1, [r1]
    str     r0, [fp, P1_OFFSET]
    str     r1, [fp, P2_OFFSET]

if:
    @ Call strcmp on two names

    ldr     r0, [fp, P1_OFFSET]
    ldr     r3, =offset_time 
    ldr     r3, [r3]
    ldr     r0, [r0, r3]                 @ get 1st time into r0
    ldr     r1, [fp, P2_OFFSET]
    ldr     r3, =offset_time            @load in the timeoffSet
    ldr     r3, [r3]
    ldr     r1, [r1,r3]                 @ get 2nd time into r1
    cmp     r0, r1
    bge     else_if

    @ return 1
    mov     r0, 1
    b       end_if

else_if:
    @ Call strcmp on two names
    ldr     r0, [fp, P1_OFFSET]
    ldr     r3, =offset_time 
    ldr     r3, [r3]
    ldr     r0, [r0,r3]                 @ get 1st time into r0
    ldr     r1, [fp, P2_OFFSET]
    ldr     r3, =offset_time            @ load in the timeoffSet 
    ldr     r3, [r3]
    ldr     r1, [r1,r3]                 @ get 2nd time into r1
    cmp     r0,r1
    ble     else

    @ return -1
    mov     r0, -1
    b   end_if

else:
    @ Else, equal, so return 0
    mov     r0, 0

end_if:
    sub sp, fp, FP_OFFSET

    @ Restore caller's registers
    pop {fp, pc}
