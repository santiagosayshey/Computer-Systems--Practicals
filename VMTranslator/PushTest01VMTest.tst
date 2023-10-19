// PushTest01VMTest.tst
load PushTest01.vm,
output-file PushTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[1]%D1.6.1 RAM[2]%D1.6.1 RAM[3]%D1.6.1 RAM[4]%D1.6.1 
            RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1 RAM[259]%D1.6.1 RAM[260]%D1.6.1
            RAM[261]%D1.6.1 RAM[262]%D1.6.1 RAM[263]%D1.6.1
            RAM[300]%D1.6.1 RAM[301]%D1.6.1 RAM[302]%D1.6.1
            RAM[303]%D1.6.1 RAM[304]%D1.6.1 RAM[305]%D1.6.1
            RAM[306]%D1.6.1 RAM[307]%D1.6.1;

set sp 256,        // stack pointer initial value
set local 300,     // 'local' segment initial value
set argument 400,  // 'argument' segment initial value
set this 3000,     // 'this' segment initial value
set that 3010,     // 'that' segment initial value
set pointer 3,     // 'pointer' segment initial value
set temp 5,        // 'temp' segment initial value

repeat 60 {
    tick;  // We use 'tick' for VMEmulator, each 'tick' executes one VM command
}
output;
