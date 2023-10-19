// GotoTest01Asm.tst
load GotoTest01.asm,
output-file GotoTest01.out,
compare-to GotoTest01.cmp,
output-list RAM[256]%D1.6.1;

set RAM[0] 256,    // stack pointer

repeat 500 {       // a large number just to ensure all ASM commands are executed
  ticktock;
}

output;
