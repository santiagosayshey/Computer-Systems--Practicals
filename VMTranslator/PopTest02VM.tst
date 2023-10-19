// PopTest02VM.tst
load PopTest02.vm,
output-file PopTest02.cmp,
output-list RAM[0]%D1.6.1 RAM[1]%D1.6.1 RAM[2]%D1.6.1 RAM[3]%D1.6.1 RAM[4]%D1.6.1 
            RAM[300]%D1.6.1 RAM[400]%D1.6.1 RAM[3000]%D1.6.1 RAM[3010]%D1.6.1;

// Set the initial values for the segments
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of this segment
set that 3010,     // base address of that segment
set sp 256,        // stack pointer

repeat 8 {
  vmstep;
}

output;
