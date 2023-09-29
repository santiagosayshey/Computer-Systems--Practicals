load ArrMin.asm,
output-file ArrMin05.out,
compare-to ArrMin05.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[40]%D2.6.2 RAM[41]%D2.6.2 RAM[42]%D2.6.2 RAM[43]%D2.6.2 RAM[44]%D2.6.2 RAM[45]%D2.6.2 RAM[46]%D2.6.2 RAM[47]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  40, // Set R1
set RAM[2]  8,  // Set R2
set RAM[40] 3,  // Set Arr[0]
set RAM[41] 0,  // Set Arr[1]
set RAM[42] -5,  // Set Arr[2]
set RAM[43] 7,  // Set Arr[3]
set RAM[44] 1,  // Set Arr[4]
set RAM[45] -2,  // Set Arr[5]
set RAM[46] 4,  // Set Arr[6]
set RAM[47] 2;  // Set Arr[7]
repeat 600 {
  ticktock;    // Run for 600 clock cycles
}
set RAM[1] 40,  // Restore arguments in case program used them
set RAM[2] 8,
output;        // Output to file
