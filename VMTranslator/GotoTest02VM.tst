// GotoTest02VM.tst
load GotoTest02.vm,
output-file GotoTest02.cmp,
output-list RAM[256]%D1.6.1 RAM[257]%D1.6.1;

set sp 256,        // stack pointer

repeat 4 {         // adjust this number based on the number of commands that should actually be executed
  vmstep;
}

output;
