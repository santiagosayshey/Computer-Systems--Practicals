// Test case 2 for ArrMax.arrMax
// Finding maximum of array: [5, 9, 7, 6]
load,
output-file ArrMax02.out,
compare-to ArrMax02.cmp,
output-list sp%D1.6.1 local%D1.6.1 argument%D1.8.1 this%D1.6.1 that%D1.6.1
            RAM[16]%D1.6.1 RAM[17]%D1.6.1 RAM[18]%D1.6.1
            local[0]%D1.8.1 local[1]%D1.8.1 local[2]%D1.8.1
            argument[0]%D1.11.1 argument[1]%D1.11.1 argument[2]%D1.11.1;

set sp 256,
set local 320,
set argument 420,
set this 3100,
set that 3120,

set RAM[16] 0,     // static 0
set RAM[17] 2056,  // static 1 - Pointer to array
set RAM[18] 4,     // static 2 - Array length

set local[0] 12,
set local[1] 24,
set local[2] 36,

set argument[0] 121,
set argument[1] 242,
set argument[2] 363,

set RAM[2056] 5,   // Set Arr[0]
set RAM[2057] 9,   // Set Arr[1]
set RAM[2058] 7,   // Set Arr[2]
set RAM[2059] 6;   // Set Arr[3]

repeat 200 {
  vmstep;
}
output;
