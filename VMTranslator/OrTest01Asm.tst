// OrTest01Asm.tst
load OrTest01.asm,
output-file OrTest01.out,
compare-to OrTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1;

set RAM[0] 256,    // stack pointer

repeat 500 {       // a large number just to ensure all ASM commands are executed
  ticktock;
}

output;