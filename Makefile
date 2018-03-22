gccParams = -m32 -std=c++11 -fno-use-cxa-atexit -nostdlib -nodefaultlibs -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fcheck-new
asmParams = --32
ldParams  = -melf_i386

INC=src/stdlib src
incParams=$(foreach d, $(INC), -I$d)

objects = obj/asm/loader.o \
          obj/stdlib/new.o \
          obj/asm/interrupta.o \
          obj/stdlib/iostream.o \
          obj/hardware/PeripheralComponentInterconnectController.o \
          obj/drivers/Keyboard.o \
          obj/drivers/Mouse.o \
          obj/memory/GlobalDescriptorTable.o \
          obj/memory/Manager.o \
          obj/interrupts/InterruptManager.o \
          obj/kernel.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc -Wall $(incParams) $(gccParams) -c -o $@ $<

obj/asm/%.o: src/asm/%.asm
	mkdir -p $(@D)
	as $(asmParams) -o $@ $<

obj/asm/%.o: src/asm/%.s
	mkdir -p $(@D)
	as $(asmParams) -o $@ $<

kernel.bin: linker.ld $(objects)
	ld $(ldParams) -T $< -o $@ $(objects)

install: kernel.bin
	sudo cp $< /boot/kernel.bin

kernel.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp $< iso/boot/
	touch iso/boot/grub/grub.cfg
	echo "set timeout=0" >> iso/boot/grub/grub.cfg
	echo "set default=0" >> iso/boot/grub/grub.cfg
	echo "" >> iso/boot/grub/grub.cfg
	echo 'menuentry "OS 42" {' >> iso/boot/grub/grub.cfg
	echo "	multiboot /boot/kernel.bin" >> iso/boot/grub/grub.cfg
	echo "	boot" >> iso/boot/grub/grub.cfg
	echo "}" >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: kernel.iso
	(killall VirtualBox && sleep 1) || true
	virtualbox --startvm "OS 42" &

.PHONY: clean
clean:
	rm -rf obj kernel.bin kernel.iso
