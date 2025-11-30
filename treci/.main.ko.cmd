cmd_/root/treci/main.ko := ld -r -m elf_i386 -T /usr/src/linux-headers-4.9.0-7-common/scripts/module-common.lds --build-id  -o /root/treci/main.ko /root/treci/main.o /root/treci/main.mod.o ;  true
