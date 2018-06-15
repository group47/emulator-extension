#use this to generate the gdb init scripts

for i in *.bin; do sed "s/a.out/$i/g; s/gdb.log/$i.log/g" < ~/gdb_init_script  > ~/gdb-take-two/arm11_47/src/emulate_extension/test_suite/ARM_MULTIPLY/$(basename "$i").gdbinit; done
