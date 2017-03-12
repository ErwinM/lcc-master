LCC retargeting thoughts
------------------------

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
