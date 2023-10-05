// Test case 1 for ArrMax.arrMax
// Finding maximum of array: [10, 3, 8, 15]
load,
output-file ArrMax01.out,
compare-to ArrMax01.cmp,
output-list sp%D1.6.1 local%D1.6.1 argument%D1.8.1 this%D1.6.1 that%D1.6.1
            RAM[16]%D1.6.1 RAM[17]%D1.6.1 RAM[18]%D1.6.1
            local[0]%D1.8.1 local[1]%D1.8.1 local[2]%D1.8.1
            argument[0]%D1.11.1 argument[1]%D1.11.1 argument[2]%D1.11.1;

set sp 256,
set local 300,
set argument 400,
set this 3000,
set that 3010,

set RAM[16] 0,     // static 0
set RAM[17] 2052,  // static 1 - Pointer to array
set RAM[18] 4,     // static 2 - Array length

set local[0] 11,
set local[1] 22,
set local[2] 33,

set argument[0] 111,
set argument[1] 222,
set argument[2] 333,

set RAM[2052] 10,  // Set Arr[0]
set RAM[2053] 3,   // Set Arr[1]
set RAM[2054] 8,   // Set Arr[2]
set RAM[2055] 15;  // Set Arr[3]

repeat 200 {
  vmstep;
}
output;
