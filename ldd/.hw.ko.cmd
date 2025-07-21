savedcmd_hw.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T /usr/src/linux-headers-6.14.0-24-generic/scripts/module.lds -o hw.ko hw.o hw.mod.o .module-common.o
