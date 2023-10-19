// PopTest02Asm.tst
load PopTest02.asm,
output-file PopTest02.out,
compare-to PopTest02.cmp,
output-list RAM[0]%D1.6.1 RAM[1]%D1.6.1 RAM[2]%D1.6.1 RAM[3]%D1.6.1 RAM[4]%D1.6.1 
            RAM[300]%D1.6.1 RAM[400]%D1.6.1 RAM[3000]%D1.6.1 RAM[3010]%D1.6.1;

// Set the initial values for the segments
set RAM[0] 256,    // stack pointer
set RAM[1] 300,    // base address of the local segment
set RAM[2] 400,    // base address of the argument segment
set RAM[3] 3000,   // base address of the 'this' segment
set RAM[4] 3010,   // base address of the 'that' segment

repeat 100 {
  ticktock;
}

output;
