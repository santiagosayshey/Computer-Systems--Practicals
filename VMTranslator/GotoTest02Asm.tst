// GotoTest02Asm.tst
load GotoTest02.asm,
output-file GotoTest02.out,
compare-to GotoTest02.cmp,
output-list RAM[256]%D1.6.1 RAM[257]%D1.6.1;  

set RAM[0] 256,    // stack pointer

repeat 1000 {      // a large number to ensure all ASM commands are executed
  ticktock;
}

output;
