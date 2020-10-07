default: cubo

cubo: multMat
	cc -no-pie proyecciones.c $<.o -lm -lSDL2 -g -o $@ 

multMat:
	nasm -f elf64 -g -F dwarf $@.asm
