// Test case 3 for ArrMax.arrMax
// Finding maximum of array: [11, 33, 22]
load,
output-file ArrMax03.out,
compare-to ArrMax03.cmp,
output-list sp%D1.6.1 local%D1.6.1 argument%D1.8.1 this%D1.6.1 that%D1.6.1
            RAM[16]%D1.6.1 RAM[17]%D1.6.1 RAM[18]%D1.6.1
            local[0]%D1.8.1 local[1]%D1.8.1 local[2]%D1.8.1
            argument[0]%D1.11.1 argument[1]%D1.11.1 argument[2]%D1.11.1;

set sp 256,
set local 340,
set argument 440,
set this 3200,
set that 3220,

set RAM[16] 0,     // static 0
set RAM[17] 2060,  // static 1 - Pointer to array
set RAM[18] 3,     // static 2 - Array length

set local[0] 13,
set local[1] 26,
set local[2] 39,

set argument[0] 131,
set argument[1] 262,
set argument[2] 393,

set RAM[2060] 11,  // Set Arr[0]
set RAM[2061] 33,  // Set Arr[1]
set RAM[2062] 22;  // Set Arr[2]

repeat 200 {
  vmstep;
}
output;
