load ArrSort.asm,
output-file ArrSort01.out,
compare-to ArrSort01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[30]%D2.6.2 RAM[31]%D2.6.2 RAM[32]%D2.6.2 RAM[33]%D2.6.2;

set PC 0,
set RAM[0]  0,
set RAM[1]  30,
set RAM[2]  4,
set RAM[30] 8,
set RAM[31] 6,
set RAM[32] 7,
set RAM[33] 9;
repeat 600 {
  ticktock;
}
set RAM[1] 30,
set RAM[2] 4,
output;
