// PushTest02Asm.tst
load PushTest02.asm,
output-file PushTest02.out,
compare-to PushTest02.cmp,
output-list RAM[0]%D1.6.1 RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1 RAM[259]%D1.6.1;

// Set the initial values for the segments
set RAM[1] 300,     // base address of the local segment
set RAM[2] 400,     // base address of the argument segment
set RAM[3] 3000,    // base address of this segment
set RAM[4] 3010,    // base address of that segment
set RAM[0] 256,     // stack pointer

// Initialize the values in the memory
set RAM[300] 111,  // local[0]
set RAM[401] 222,  // argument[1]
set RAM[3002] 333, // this[2]
set RAM[3013] 444, // that[3]

repeat 100 {
  ticktock;
}

output;
