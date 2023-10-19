// LabelTest02VM.tst
load LabelTest02.vm,
output-file LabelTest02.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1;

set sp 256,        // stack pointer

repeat 2 {         // number of commands in the VM file
  vmstep;
}

output;
