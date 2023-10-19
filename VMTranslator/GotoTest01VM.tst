// GotoTest01VM.tst
load GotoTest01.vm,
output-file GotoTest01.cmp,
output-list RAM[256]%D1.6.1;

set sp 256,        // stack pointer

repeat 3 {         // number of commands in the VM file, adjusted based on the actual VM commands
  vmstep;
}

output;
