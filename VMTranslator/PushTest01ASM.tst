// PushTest01Asm.tst
load PushTest01.asm,
output-file PushTest01.out,
compare-to PushTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1;

set RAM[0] 256, // stack pointer

repeat 100 {
  ticktock;
}

output;
