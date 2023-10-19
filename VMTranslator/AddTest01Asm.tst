// AddTest01Asm.tst
load AddTest01.asm,
output-file AddTest01.out,
compare-to AddTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1;

set RAM[0] 256,    // stack pointer

repeat 100 {       // a large number just to ensure all ASM commands are executed
  ticktock;
}

output;
