// Test file for Abs.asm: Abs03.tst
// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load Abs.asm,
output-file Abs03.out,
compare-to Abs03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] -5;  // Set R1 (value to get the absolute of)
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] -5,  // Restore argument in case program used it
output;        // Output to file
