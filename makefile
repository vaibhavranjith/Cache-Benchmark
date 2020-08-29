run:sim.out
	./sim.out 8192 32 8 "IJPEG.DAT"
sim.out:sim.c
	gcc -o sim.out sim.c create_cache.c -lm 
