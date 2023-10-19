// IfGotoTest01VM.tst
load IfGotoTest01.vm,
output-file IfGotoTest01.cmp,
output-list RAM[256]%D1.6.1;

set sp 256,        // stack pointer

repeat 4 {         // number of commands in the VM file
  vmstep;
}

output;
