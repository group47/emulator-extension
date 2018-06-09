for i in *.bin2; do echo $i;python3 comparison_script.py /homes/fpn17/CLionProjects/arm11_47/src/cmake-build-debug/emulate_extension $(basename $i .bin2);  done
