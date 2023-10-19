// PushTest01VM.tst
load PushTest01.vm,
output-file PushTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1;

set sp 256, // stack pointer

repeat 3 {
  vmstep;
}

output;
