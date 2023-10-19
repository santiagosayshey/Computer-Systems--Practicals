// PushTest02VM.tst
load PushTest02.vm,
output-file PushTest02.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1 RAM[259]%D1.6.1;

// Set the initial values for the segments
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of this segment
set that 3010,     // base address of that segment

// Initialize the values in the memory
set RAM[300] 111,  // local[0]
set RAM[401] 222,  // argument[1]
set RAM[3002] 333, // this[2]
set RAM[3013] 444, // that[3]

repeat 4 {
  vmstep;
}

output;
