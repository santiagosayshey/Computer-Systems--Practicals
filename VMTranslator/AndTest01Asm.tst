// AndTest01Asm.tst
load AndTest01.asm,
output-file AndTest01.out,
compare-to AndTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1;

set RAM[0] 256,    // stack pointer

repeat 500 {       // a large number just to ensure all ASM commands are executed
  ticktock;
}

output;
