/*
    A Linux Process's memory layout (userspace)

     |_____________________|
     |  command line args  |
     |        and          |
     |environment variables|
     |_____________________| 
     |                     | Call Stack
     |                     |  
     |                     |  
     |.....................| 
     |                     |
     |                     |  
     |                     |   
     |                     |
     |                     |  Heap memory area (malloc() and free())
     |                     |
     |                     |  
     |                     |   
     |_____________________| 
     |                     |
     |                     |  Global memory area
     |                     |  
     |_____________________|  
     |                     |
     |                     |  Code Area
     |_____________________| 
     |                     |

A process can be thought of as an instance of a running program.

Its memory space consists of:

Code area
    contains the machine code instructions for the program

    In C:
    after compiling, the machine code of functions will be put in the code area.

Data area

    Global memory area
        contains global/static variables and constant strings.
        Its size is often determined by the compiler and linker when building the program, not at run time.

        Their lifetime extends throughout the entire execution of the program.

    Heap memory area
        dynamically allocated via malloc()/free().
        C programers are responsible for calling malloc() and free().

        Variables allocated on the heap have a dynamic lifetime, controlled by the programmer.
        A heap-allocated variable itself doesn't have any name,
        so it should be accessed via a pointer variable.

    Call stack 
        dynamically-allocated due to function calls/returns.
        The push operation (creating a new frame) is caused by a function call (generated by the compiler),
        while its pop operation (removing a frame) is caused by a function return (generated by the compiler).
        It consists of stack frames (First-In-Last-Out), one for each called function.
        Each frame might contain the return address, local variables, parameters, and temporary variables.

        Since different functions can have different sets of local variables, their stack frames vary in size.

        Local variables are declared within a function and are only accessible within that function's scope.
        Their lifetime is limited to the duration of the function call in which they are declared.   

--------------------------------------------------------------------------------------------

Pointer operator

    In C, the asterisk operator, *, is used to declare and manipulate pointers.

Address operator

    It is denoted as the ampersand symbol, &.


For example

    int n = 2024;
    int *ptr = &n;

                   
Its memory layout:

                --------
    ptr  ---->    2024
                --------
                 int n
               

More details are discussed in COMP9024/C/AccessMemory

                                                    COMP9024
 */
#include <stdio.h>    // for printf()
#include <stdlib.h>   // for malloc() and free()


// global variable, visible in all *.c files in the same C project
long year = 2024;

// The default value of a global/static variable is 0
// The static variable 'number' is visible in the current C file.
// In this way, we can hide the implementation and expose a smaller interface (declarations in *.h) to other C files.
static int number;

/* 
    "CSE@UNSW" is a constant string.
    cptr is a pointer which points to the first character of "CSE@UNSW"

    Memory Layout:
                   -------------
    cptr ----->     "CSE@UNSW"
                   -------------
 */

char *cptr ="CSE@UNSW";

// test1() is a global function, visible in all *.c files in the same C project
int test1(void) {
    printf("test1()\n");
    return 2024;
}

// test2() is a static function, visible in the current *.c file
static int test2(void) {
    // 'count' is a static variable (NOT on call stack), but only visible in test2()
    static int count = 0;            
    // How many times test2() has been called
    count++;

    printf("test2() has been called %d times\n", count);
    return 2025;
}

// Define a function pointer type, which points to a function whose type is 'int (void)'.
typedef int (*FuncPtrTy)(void);


static void g(void){
    // 'x' is a local variable
    int x = 30;    

    printf("g(): x == %d, &x == %p\n", x, &x);
 }

// 'fptr' is a function parameter
static void TestPolymorphism(FuncPtrTy fptr) {
    printf("\nInside TestPolymorphism(): \n");
    /*
        Memory Layout

        When TestPolymorphism(&test2) is invoked:

                               ----------------
        --------                  test2:
         &test2    ---------->       machine instruction
        --------                     machine instruction
    FuncPtrTy fptr                   ...
                                     ret               // the 'ret' instruction will pop the return address from the call stack

                                  test1:
                                     machine instruction
                                     machine instruction
                                     ...
                                     ret
                                
                                  g:
                                     machine instruction
                                     ...
                                     ret
     
                       TestPolymorphism:
                                     ...               // The address of the instruction after 'a call instruction' is its return address.
                                     
                                     call *fptr        // Save 'return_addr1' on the call stack and jump to the target function
                      return_addr1:                                   
                                     ...
     
                                     call g            // Save 'return_addr2' on the call stack and jump to the target function
                      return_addr2:
                                     ...
                                 -----------------
        Data Area                   Code Area

     */    
    /*
     fptr() is an indirect function call (as shown in the 'call *fptr' above),
        where the address of the target function needs to be loaded from 'fptr' in the data area. 

     Polymorphism:
        The identical machine code, represented by 'call *fptr', within the code area, exhibits varying behaviors. 

        (1) when TestPolymorphism(test1) is invoked, 
            'call *fptr' will call test1()

        (2) when TestPolymorphism(&test2) is invoked,
            'call *fptr' will call test2()
    
     */
    int val = fptr();
    printf("fptr() == %d, fptr == %p, &fptr == %p\n", val, fptr, &fptr);
    // g() is a direct function call, where the address of g() is hard-coded in the code area ('call g')
    g();    
}

void TestMemoryLayout(void){
    /*
                    --------
        pLong ---->   2024 
                    --------
                    heap-allocated variable (unnamed)
     */
    long *pLong = (long *) malloc(sizeof(long));
    *pLong = 2024;
    printf("\n\n*pLong == %ld, pLong == %p, &pLong == %p\n\n", *pLong, pLong, &pLong);    

    // C compiler treats the function name specially.    
    // Both 'test1' and '&test1' represent the function address of test1()
    TestPolymorphism(test1);
    
    // C compiler treats the function name specially.
    // Both 'test2' and '&test2' represent the function address of test2()
    TestPolymorphism(&test2);   
    
    free(pLong);
}

