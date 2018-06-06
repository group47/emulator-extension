#in no particular order

#gdb scripts
for i in *.s; do sed "s/a.out/$(basename $i .s).actuallyanexecutable/g; s/gdb.log/$i.log/g" < ~/gdb_init_script  > ~/gdb-take-two/arm11_47/src/emulate_extension/test_suite/general_tests/thumb/$(basename "$i" .s).gdbinit; done

#extract useable assembly from disassembly
#for i in *.bin; do objdump -D $i --target=binary --architecture=arm_any| grep -o -P 'm[lu][a-z]+[^A;]+' > $(basename $i .bin).s; done

#assemble
for i in *.s; do gcc -mthumb -c $i -o $(basename $i .s).realbin; done

#link
for i in *.realbin; do gcc $i -o $(basename $i .realbin).actuallyanexecutable -nostdlib; done

#run gdb
for i in *.actuallyanexecutable; do gdb -q --command=$(basename $i .actuallyanexecutable).gdbinit > $(basename $i .actuallyanexecutable).log; done
#for i in *.actuallyanexecutable; do gdb -q --command=$(basename $i .actuallyanexecutable).gdbinit; done # | grep -v ?? | grep -v "\n" | grep -v "GNU" | grep -v "help"> $(basename $i .actuallyanexecutable).log; done

#extract bin

for i in *.realbin; do objcopy -O binary $i --only-section=.text  $(basename $i .realbin).bin2; done
