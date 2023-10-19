// PushTest01ASMTest.tst
load PushTest01.asm,   // this assumes that your VMTranslator generates a file named PushTest01.asm
output-file PushTest01.out,
compare-to PushTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[1]%D1.6.1 RAM[2]%D1.6.1 RAM[3]%D1.6.1 RAM[4]%D1.6.1 
            RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1 RAM[259]%D1.6.1 RAM[260]%D1.6.1
            RAM[261]%D1.6.1 RAM[262]%D1.6.1 RAM[263]%D1.6.1
            RAM[300]%D1.6.1 RAM[301]%D1.6.1 RAM[302]%D1.6.1
            RAM[303]%D1.6.1 RAM[304]%D1.6.1 RAM[305]%D1.6.1
            RAM[306]%D1.6.1 RAM[307]%D1.6.1;

set RAM[0] 256,     // stack pointer initial value
set RAM[1] 300,     // 'local' segment initial value
set RAM[2] 400,     // 'argument' segment initial value
set RAM[3] 3000,    // 'this' segment initial value
set RAM[4] 3010,    // 'that' segment initial value
set RAM[5] 3,       // 'pointer' segment initial value
set RAM[6] 5,       // 'temp' segment initial value

repeat 480 {  // 'ticktock' for CPUEmulator, each 'ticktock' executes one assembly instruction
    ticktock;
}
output;
