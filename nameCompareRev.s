/*
 * Filename: nameCompareRev.s
 * Author: Jason Chau
 * Userid: cs30fie
 * Description: defines the nameCompare funtion that is passed in as
 *              parameter for qsort() function used in the PA4 program.
 * Date: 11/28/18
 * Sources of Help: Piazza
 */

.syntax unified

.equ FP_OFFSET, 4
.equ PARAM_SPACE, 16
.equ P1_OFFSET, -8
.equ P2_OFFSET, -12

.text
.align 2
.global nameCompareRev

/*
 * Function name: nameCompareRev()
* Function prototype: int nameCompareRev(cons void * p1, const void * p2);
 * Description: This funcion will defines the nameCompare funtion
 that is passed in as parameter for qsort() function used in the 
 PA4 program.
 * Parameters: p1 is a pointer to a struct
 * p2 is a pointer to a struct
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: 1, if name is smaller, 0 if same , -1 if name is larger
 * Registers Used: 
 *  r0 - time of first struct
 *  r1 - time of second struct
 */
nameCompareRev:
    @ Save caller's registers on the stack
    push {fp, lr}

    add     fp, sp, FP_OFFSET
    sub     sp, sp, PARAM_SPACE
    str     r0, [fp, P1_OFFSET]
    str     r1, [fp, P2_OFFSET]

if:
    @ Call strcmp on two names

    ldr     r0, [fp, P1_OFFSET]
    ldr     r0, [r0]                 @ get 1st name into r0
    ldr     r1, [fp, P2_OFFSET]
    ldr     r1, [r1]                 @ get 2nd name into r1
    bl      strcmp

    @ strcmp returned value < 0, first < second
    cmp     r0, 0
    bge     else_if
    @ return 1
    mov     r0, 1
    b       end_if

else_if:
    @ Call strcmp on two names
    ldr     r0, [fp, P1_OFFSET]
    ldr     r0, [r0]                 @ get 1st name into r0
    ldr     r1, [fp, P2_OFFSET]
    ldr     r1, [r1]                 @ get 2nd name into r1
    bl      strcmp

    @ strcmp returned value > 0, first > second
    cmp     r0, 0

    ble     else
    @ return -1
    mov     r0, -1
    b       end_if

else:
    @ Else, equal, so return 0
    mov     r0, 0

end_if:
    sub sp, fp, FP_OFFSET

    @ Restore caller's registers
    pop {fp, pc}
