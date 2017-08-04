LCC retargeting thoughts
------------------------

$ cd lcc
$ mkdir build
$ export BUILDDIR=./build
$ make ./build/rcc
$ build/rcc -target=x86/linux tst/8q.c




function:

branch is load pc with another value
call is deal with a return value
ret is return pc to return value


at function entry we need to:
* make room for the frame on the stack (decrease SP)
* save the return value on stack (no link reg - KISS!)


at function return we need to:
- put return value in R1 (?)
- load PC with return value


push / pop:
I think i want to use this idiom. I understand that relatively well. It's also not that hard to implement in the CPU instruction set.
I am abit worried about the imm offset mem ops only working from bp. that means all global memory access will go from an index. Only one extra
load but it does need an additional reg.

I have opcode 2 and 3 still available so could use those for ld and st words perhaps..

lets implement push / pop and see about getting the first program to execute on the simulator. => DONE

A function call needs to push PC + 1 (PC points to the branch instruction!). I could do this with a seperate pushret instruction, but that costs me an instruction. it does save an instruction (addi Rx, 1, PC) per function call. And we will be calling functions like no body's business => WRONG, pushret would have to use an immediate (MDR) and store the result of a computation in mem (via MDR). this doesn't work in a store/load achitercure (note to self: it COULD work if there was a separate IMM register)..

load/store addressing:
- often the compiler does not know the required displacement (symbol!); these are not known before linking
- we should use a conservative approach and only use instructions with limited displacement if we know the required displacement
- this means a compiler cannot really utilize a base + index addressing since it does not know what the value should be: it does not place things in memory
- the things is does place in memory (stack) has known pointers (and often limited displacement)
- base index addressing prob means index that scales to easily address arrrays (i dont understand this completely)
- for most purposes it will just be 'base' addressing - where base holds the location (symbol)
- lda can only load a 10b signed imm 512 bytes of displacement
- an assembler macro will be used to load a higher imm in the base address
- now how the F**K do I implement this in LCC...

Problems to solve
-----------------
* loading a signed int to a register probably wont extend the sign in the register (which will be wider) at this point

* arguments larger than a word are not handled properly (they cannot be pushed and need to be copied)

* main does not return correct if there is no local variable set

BP
--
LCC doesnt really require a base pointer since it can calculate offsets using the framesize
However, my imm addressing modes only work of reg5 anyway...
=> lets go with it for now

ONCHIP Memory conventions
-------------------------
sp -> 2000 to start

SCRATCH MEMORY
--------------
Because I will use some monkey patching code for instructions like mult and div, I need some memory to be able to free a register to work with (and restore before returning).

- i will get 2 reg with the operands. I could use the stack. Prob the most elegant solution.
- let's try to implement mult


List of "TO FIX":
-----------------
- CVUI4 is not actually converting but a stub to make code compile atm
