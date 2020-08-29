gcc -o sim.out sim.c create_cache.c -lm
cache_size=( 2048 4096 8192 16384 )
cache_line_size=( 8 16 32 64 128 )
cache_assoc=( 2 4 8 16 )
echo -e "SIMULATION OUT\n" |cat >Simout 
for(( i=0; i<4; i++ ))
do 
	for(( j=0; j<4; j++ ))
	do
		for(( k=0; k<4; k++ ))
		do
			echo "${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} simulating"
			echo -e "\n\n 			${cache_size[$i]} 	${cache_line_size[$j]} 	${cache_assoc[$k]}\n\n\n"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "IJPEG.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "GO.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "LI.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "MGRID.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "SWIM.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "VORTEX.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "APPLU.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "CC1.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "HYDRO2D.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "M88KSIM.DAT"|cat>>Simout;	
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "TOMCATV.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "APSI.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "compress95.dat"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "FPPPP.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "PERL.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "SU2COR.DAT"|cat>>Simout;
			./sim.out ${cache_size[$i]} ${cache_line_size[$j]} ${cache_assoc[$k]} "TURB3D.DAT"|cat>>Simout;
		done
	done
done
gedit Simout &	
