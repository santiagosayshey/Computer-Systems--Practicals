load ArrMin.asm,
output-file ArrMin04.out,
compare-to ArrMin04.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[60]%D2.6.2 RAM[61]%D2.6.2 RAM[62]%D2.6.2 RAM[63]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  60, // Set R1
set RAM[2]  4,  // Set R2
set RAM[60] 9,  // Set Arr[0]
set RAM[61] 8,  // Set Arr[1]
set RAM[62] 7,  // Set Arr[2]
set RAM[63] 6;  // Set Arr[3]
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 60,  // Restore arguments in case program used them
set RAM[2] 4,
output;        // Output to file