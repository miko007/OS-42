gppParams = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
asmParams = --32
ldParams  = -melf_i386

INC=src/stdlib src
incParams=$(foreach d, $(INC), -I$d)

objects = obj/asm/loader.o \
          obj/asm/interrupta.o \
          obj/stdlib/iostream.o \
          obj/memory/GlobalDescriptorTable.o \
          obj/interrupts/InterruptManager.o \
          obj/kernel.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc -Wall $(incParams) $(gppParams) -c -o $@ $<

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
