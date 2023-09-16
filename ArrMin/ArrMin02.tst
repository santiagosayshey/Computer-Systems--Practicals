load ArrMin.asm,
output-file ArrMin02.out,
compare-to ArrMin02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[40]%D2.6.2 RAM[41]%D2.6.2 RAM[42]%D2.6.2 RAM[43]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  40, // Set R1
set RAM[2]  4,  // Set R2
set RAM[40] 3,  // Set Arr[0]
set RAM[41] 5,  // Set Arr[1]
set RAM[42] 6,  // Set Arr[2]
set RAM[43] 1;  // Set Arr[3]
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 40,  // Restore arguments in case program used them
set RAM[2] 4,
output;        // Output to file
