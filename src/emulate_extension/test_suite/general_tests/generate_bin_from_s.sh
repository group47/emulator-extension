for i in *.s; do gcc -c $i -o $(basename $i .s).realbin; done

#link
for i in *.realbin; do gcc $i -o $(basename $i .realbin).actuallyanexecutable -nostdlib; done

#run gdb
for i in *.actuallyanexecutable; do gdb --command=$(basename $i .actuallyanexecutable).gdbinit > $(basename $i .actuallyanexecutable).log; done

#extract bin

for i in *.realbin; do objcopy -O binary $i --only-section=.text  $(basename $i .realbin).bin2; done

