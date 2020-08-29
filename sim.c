#include<stdlib.h>
#include<stdio.h>
#include"Cache.h"
int main(int argv,char* argc[]){
	Cache cache,cache1,cache2;
	cache.cache_size=atoi(argc[1]);
	cache.block_size=atoi(argc[2]);
	cache.assoc=atoi(argc[3]);
	cache1.cache_size=atoi(argc[1]);
	cache1.block_size=atoi(argc[2]);
	cache1.assoc=atoi(argc[3]);
	cache2.cache_size=atoi(argc[1]);
	cache2.block_size=atoi(argc[2]);
	cache2.assoc=atoi(argc[3]);
	FILE* fp=fopen(argc[4],"r");
	printf("TEST FILE:: ***%s***\n",argc[4]);
	printf("##########################################################################\n");
	if(create_cache(&cache)){
	printf("@@@@@@@@@@@@@@@@ 	CONVENTIONAL CACHE	@@@@@@@@@@@@@@@@@@@@@@@@@@\n");	
		read_cnvcache(fp,&cache);
		//fclose(fp);	
	}
	printf("==========================================================================\n");
	fseek(fp,0,SEEK_SET);
	if(create_cache(&cache1)){
	printf("@@@@@@@@@@@@@@@@ 	WAY-PREDICTION CACHE	@@@@@@@@@@@@@@@@@@@@@@@@@@\n");	
		read_wpcache(fp,&cache1);	
	}
	printf("==========================================================================\n");
	fseek(fp,0,SEEK_SET);
	if(create_cache(&cache2)){
	printf("@@@@@@@@@@@@@@@@ 	WAY-HALTING CACHE	@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		read_whcache(fp,&cache2);	
	}
	
	printf("##########################################################################\n");
	fclose(fp);
	
}
