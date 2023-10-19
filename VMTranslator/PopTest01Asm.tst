// PopTest01Asm.tst
load PopTest01.asm,
output-file PopTest01.out,
compare-to PopTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[1]%D1.6.1 RAM[2]%D1.6.1 RAM[3]%D1.6.1 RAM[4]%D1.6.1 
            RAM[300]%D1.6.1 RAM[401]%D1.6.1 RAM[3002]%D1.6.1 RAM[3013]%D1.6.1;

// Set the initial values for the segments
set RAM[1] 300,     // base address of the local segment
set RAM[2] 400,     // base address of the argument segment
set RAM[3] 3000,    // base address of this segment
set RAM[4] 3010,    // base address of that segment
set RAM[0] 256,     // stack pointer

repeat 200 {
  ticktock;
}

output;
