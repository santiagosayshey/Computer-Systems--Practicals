load ArrSort.asm,
output-file ArrSort01.out,
compare-to ArrSort01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[20]%D2.6.2;

set PC 0,
set RAM[0]  0,
set RAM[1]  20,
set RAM[2]  1,
set RAM[20] 5;
repeat 200 {
  ticktock;
}
set RAM[1] 20,
set RAM[2] 1,
output;
