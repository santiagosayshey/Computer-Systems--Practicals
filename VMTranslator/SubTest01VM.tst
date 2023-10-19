// SubTest01VM.tst
load SubTest01.vm,
output-file SubTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1;

set sp 256,        // stack pointer

repeat 3 {         // number of commands in the VM file
  vmstep;
}

output;
