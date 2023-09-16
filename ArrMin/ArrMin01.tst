load ArrMin.asm,
output-file ArrMin01.out,
compare-to ArrMin01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[30]%D2.6.2 RAM[31]%D2.6.2 RAM[32]%D2.6.2 RAM[33]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  30, // Set R1
set RAM[2]  4,  // Set R2
set RAM[30] 8,  // Set Arr[0]
set RAM[31] 6,  // Set Arr[1]
set RAM[32] 7,  // Set Arr[2]
set RAM[33] 9;  // Set Arr[3]
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 30,  // Restore arguments in case program used them
set RAM[2] 4,
output;        // Output to file
