// IfGotoTest01Asm.tst
load IfGotoTest01.asm,
output-file IfGotoTest01.out,
compare-to IfGotoTest01.cmp,
output-list RAM[256]%D1.6.1;

set RAM[0] 256,    // stack pointer

repeat 500 {       // a large number just to ensure all ASM commands are executed
  ticktock;
}

output;
