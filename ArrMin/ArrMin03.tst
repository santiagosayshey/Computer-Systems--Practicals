load ArrMin.asm,
output-file ArrMin03.out,
compare-to ArrMin03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[50]%D2.6.2 RAM[51]%D2.6.2 RAM[52]%D2.6.2 RAM[53]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  50, // Set R1
set RAM[2]  4,  // Set R2
set RAM[50] 5,  // Set Arr[0]
set RAM[51] 4,  // Set Arr[1]
set RAM[52] 3,  // Set Arr[2]
set RAM[53] 2;  // Set Arr[3]
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 50,  // Restore arguments in case program used them
set RAM[2] 4,
output;        // Output to file