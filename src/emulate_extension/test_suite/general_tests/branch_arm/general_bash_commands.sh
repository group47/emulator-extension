#in no particular order


#extract bin




#for i in *.realbin; do objcopy -O binary $i --only-section=.text --only-section=.data $(basename $i .realbin).bin2; done
#for i in *.realbin; do objcopy -O binary $i --only-section=.text  $(basename $i .realbin).bintext; done
#for i in *.realbin; do objcopy -O binary $i --only-section=.data  $(basename $i .realbin).bindata; done

#for i in *.realbin; do cat $(basename $i .realbin).bintext > $(basename $i .realbin).bin3; done
#for i in *.realbin; do
#  text_loc=$((0x$(objdump -x $(basename $i .realbin).actuallyanexecutable | grep -oP 'text         [0-9a-f]+  [0-9a-f]+  [0-9a-f]+  [0-9a-f]+' | sed -e 's/  / /g' |  sed -e 's/  / /g'| sed -e 's/  / /g'| sed -e 's/  / /g' | sed -e 's/text //g' | sed -e 's/[0-9a-f]* //g' | sed -e 's/[0-9a-f]* //g' | sed -e 's/[0-9a-f]* //g')));
#  echo $text_loc
#  data_loc=$((0x$(objdump -x $(basename $i .realbin).actuallyanexecutable | grep -oP 'data         [0-9a-f]+  [0-9a-f]+  [0-9a-f]+  [0-9a-f]+' | sed -e 's/  / /g' |  sed -e 's/  / /g'| sed -e 's/  / /g'| sed -e 's/  / /g' | sed -e 's/data //g' | sed -e 's/[0-9a-f]* //g' | sed -e 's/[0-9a-f]* //g' | sed -e 's/[0-9a-f]* //g'))); 
#  echo $data_loc
#  dd if=/dev/null of=$(basename $i .realbin).bin3 seek=$(expr $data_loc - $text_loc) bs=1; 
#done

#for i in *.realbin; do head -c -3 -q $(basename $i .realbin).bintext $(basename $i .realbin).bindata > $(basename $i .realbin).bin3 ; done




#gdb scripts
for i in *.s; do sed "s/a.out/$(basename $i .s).actuallyanexecutable/g; s/gdb.log/$i.log/g; s/mem.bin/$(basename $i .s).bin2/g" < ~/gdb_init_script2  > ~/gdb-take-two/arm11_47/src/emulate_extension/test_suite/general_tests/branch_arm/$(basename "$i" .s).gdbinit; done

#extract useable assembly from disassembly
#for i in *.bin; do objdump -D $i --target=binary --architecture=arm_any| grep -o -P 'm[lu][a-z]+[^A;]+' > $(basename $i .bin).s; done

#assemble
for i in *.s; do gcc -c $i -o $(basename $i .s).realbin; done

#link
for i in *.realbin; do gcc $i -o $(basename $i .realbin).actuallyanexecutable -nostdlib; done

#run gdb
for i in *.actuallyanexecutable; do gdb -q --command=$(basename $i .actuallyanexecutable).gdbinit >  $(basename $i .actuallyanexecutable).log; done
#for i in *.actuallyanexecutable; do gdb -q --command=$(basename $i .actuallyanexecutable).gdbinit; done # | grep -v ?? | grep -v "\n" | grep -v "GNU" | grep -v "help"> $(basename $i .actuallyanexecutable).log; done


