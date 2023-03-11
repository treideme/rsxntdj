@echo .globl _%1; .text; _%1: jmp _%2 | as -o %3
