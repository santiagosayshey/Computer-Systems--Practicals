// PopTest01VM.tst
load PopTest01.vm,
output-file PopTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[1]%D1.6.1 RAM[2]%D1.6.1 RAM[3]%D1.6.1 RAM[4]%D1.6.1 
            RAM[300]%D1.6.1 RAM[401]%D1.6.1 RAM[3002]%D1.6.1 RAM[3013]%D1.6.1;

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
