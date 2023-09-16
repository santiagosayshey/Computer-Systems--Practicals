// Test file: Abs01.tst
load Abs.asm,
output-file Abs01.out,
compare-to Abs01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 5;  // Set R1 to a positive value
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 5,  // Restore arguments in case program used them
output;        // Output to file