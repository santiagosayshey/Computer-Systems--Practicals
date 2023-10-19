// IfGotoTest02Asm.tst
load IfGotoTest02.asm,
output-file IfGotoTest02.out,
compare-to IfGotoTest02.cmp,
output-list RAM[256]%D1.6.1;

set RAM[0] 256,    // stack pointer

repeat 500 {       // just to ensure all ASM commands are executed
  ticktock;
}

output;
