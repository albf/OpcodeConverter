#!/bin/bash

echo ~/ellcc/bin/ecc -target mips-linux-eng -S src/${1}.c -I ../MipsCTestCases/extras/lib/ -nostdlib -fno-exceptions -fno-rtti -static -o bin2/${1}.s

~/ellcc/bin/ecc -target mips-linux-eng -S src/${1}.c -I ../MipsCTestCases/extras/lib/ -nostdlib -fno-exceptions -fno-rtti -static -o bin2/${1}.s

echo /opt/cross/mips-unknown-linux-gnu/bin/as bin2/${1}.s ../MipsCTestCases/extras/crt0.s ../MipsCTestCases/extras/lib/THING_ultrasonic.s ../MipsCTestCases/extras/lib/THING_serial.s ../MipsCTestCases/extras/lib/THING_encoder.s ../MipsCTestCases/extras/lib/THING_movement.s -o bin2/${1}.o

/opt/cross/mips-unknown-linux-gnu/bin/as bin2/${1}.s ../MipsCTestCases/extras/crt0.s ../MipsCTestCases/extras/lib/THING_ultrasonic.s ../MipsCTestCases/extras/lib/THING_serial.s ../MipsCTestCases/extras/lib/THING_encoder.s ../MipsCTestCases/extras/lib/THING_movement.s -o bin2/${1}.o

echo /opt/cross/mips-unknown-linux-gnu/bin/ld -T ../MipsCTestCases/linker.ld bin2/${1}.o -o bin2/${1}.bin

/opt/cross/mips-unknown-linux-gnu/bin/ld -T ../MipsCTestCases/linker.ld bin2/${1}.o -o bin2/${1}.bin

echo /opt/cross/mips-unknown-linux-gnu/bin/objcopy -O binary bin2/${1}.bin bin2/${1}.x

/opt/cross/mips-unknown-linux-gnu/bin/objcopy -O binary bin2/${1}.bin bin2/${1}.x
