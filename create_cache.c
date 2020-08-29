#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"Cache.h"
#include<math.h>
#define BLOCK_ADDRESS		1
#define BLOCK_OFFSET		2
#define INDEX			3
#define _TAG			4		

int create_cache(Cache* cache){
	int bz,asc,cz;
	bz=cache->block_size;
	asc=cache->assoc;
	cz=cache->cache_size;
	int i,j;
	cache->cache_set=malloc((cz/(asc*bz))*sizeof(Cache_set));	//cache size/associativity gives total number of sets
	if(cache->cache_set==NULL)return 0;
	for(i=0;i<(cz/(bz*asc));i++){
		cache->cache_set[i].block=malloc(asc*sizeof(Block));
		if(cache->cache_set[i].block==NULL) return 0;
		for(j=0;j<asc;j++){						//creating cache 
			cache->cache_set[i].block[j].line=(char*)malloc(bz*sizeof(char));	
			if(cache->cache_set[i].block[j].line==NULL)return 0;
			
		}
	}
	
	printf("\nCache creation SUCCESSFUL.\n");
	return 1;		//cache sucessfully allocated
				
}	
	
unsigned int parse(unsigned int address,Cache cache,int par){
	unsigned int mask1=cache.block_size-1;
	unsigned int mask2=(cache.cache_size)/(cache.assoc*cache.block_size)-1;
	unsigned int blockaddress=(address&(~mask1))>>(unsigned int)log2f(cache.block_size);
	if(par==BLOCK_ADDRESS)
		return address&(~mask1);
	else if(par==BLOCK_OFFSET)
		return address&mask1;
	else if(par==INDEX)
		return blockaddress&mask2;
	else if(par==_TAG)
		return (blockaddress&(~mask2))>>(unsigned int)log2f((cache.cache_size)/(cache.assoc*cache.block_size));		
}

void print_cache(Cache cache){
	int i,j;
	for(i=0;i<(cache.cache_size/(cache.assoc*cache.block_size));i++){
		for(j=0;j<cache.assoc;j++){
			printf("%d  %d  	",cache.cache_set[i].block[j].valid,cache.cache_set[i].block[j].tag);
			printf("%d  	",cache.cache_set[i].block[j].LRU);
			for(int k=0;k<cache.block_size;k++)
				printf("%d 	",(int)cache.cache_set[i].block[j].line[k]);
				printf("\n");
		}
	printf("======================================================================================================================\n");
		
	}

}
void read_cnvcache(FILE* fp, Cache* cache){
	int i,j,flag;
	cache->hits=0;
	cache->TNi=0;
	unsigned int address,set,TAG;
	while(1){
		flag=0;
		fscanf(fp,"%x",&address);
		if(feof(fp))break;				
		set=parse(address,*cache,INDEX);
		TAG=parse(address,*cache,_TAG);
		for(int i=0;i<cache->assoc;i++){
			if(cache->cache_set[set].block[i].tag==TAG && cache->cache_set[set].block[i].valid==1){
				cache->hits++;
				flag=1;
				if(cache->cache_set[set].block[i].LRU!=cache->assoc-1){
					cache->cache_set[set].block[i].LRU=cache->assoc-1;
					for(int j=0;j<cache->assoc-1;j++){
						i++;
						if(i>=cache->assoc)
							i=0;
						if(cache->cache_set[set].block[i].LRU>0)
							cache->cache_set[set].block[i].LRU--;
					}
				}
				break;
			}
		}
		if(flag==0){
			
				for(int i=0;i<cache->assoc;i++){
					if(cache->cache_set[set].block[i].LRU==0){
						cache->cache_set[set].block[i].LRU=cache->assoc-1;
						cache->cache_set[set].block[i].valid=1;	//moving block from memory
						cache->cache_set[set].block[i].tag=TAG;
						cache->cache_set[set].MRU=i;		//updating MRU
						for(int j=0;j<cache->assoc-1;j++){
							i++;
							if(i>=cache->assoc)
								i=0;		//loop to udate all LRU values
							if(cache->cache_set[set].block[i].LRU>0)
								cache->cache_set[set].block[i].LRU--;
						}
						break;	
					}
				}
				
		}
		cache->TNi++;
	}
		printf("Number of misses:: %d\nNumber of hits:: %d\n",cache->TNi-cache->hits,cache->hits);
		printf("Number of instructions:: %d\n",cache->TNi);				
}

void read_wpcache(FILE* fp, Cache* cache){		//way predicted access
	int i,j;
	cache->hits=0;
	float nwo=0;
	float ph=0;
	int phch=0;
	int pmch=0;
	int flag=0;
	float tni=0;
	int compulmiss=0;
	int confmiss=0;
	int capmiss=0;
	//int* adr_spc1=malloc((pow(2,32)/cache->block_size)*sizeof(int));
	unsigned int address,set,TAG,pred_way;
	while(1){
		flag=0;
		fscanf(fp,"%x",&address);
		if(feof(fp))break;				
		set=parse(address,*cache,INDEX);
		pred_way=cache->cache_set[set].MRU;
		TAG=parse(address,*cache,_TAG);
		//cycle 1 predicted way
		nwo=nwo+1;
		if(cache->cache_set[set].block[pred_way].valid==1 && cache->cache_set[set].block[pred_way].tag==TAG){
			cache->hits++;
			ph=ph+1;
			flag=1;
			
		}
		//cycle 2 fires up all other ways and checks for valid bit and tag value
		else{
			nwo=nwo+(cache->assoc-1);
			for(i=0;i<cache->assoc-1;i++){
				pred_way++;
				if(pred_way==cache->assoc)
					pred_way=0;
				if(cache->cache_set[set].block[pred_way].valid==1 && cache->cache_set[set].block[pred_way].tag==TAG){
					cache->hits++;
					cache->cache_set[set].block[pred_way].LRU=cache->assoc-1;
					cache->cache_set[set].MRU=pred_way;
					for(int j=0;j<cache->assoc-1;j++){
						pred_way++;
						if(pred_way>=cache->assoc)
							pred_way=0;		//loop to update all LRU value
						if(cache->cache_set[set].block[pred_way].LRU>0)
							cache->cache_set[set].block[pred_way].LRU--;
					}
					flag=1;
					pmch++;
					break;
				}
			}
		}	
		if(flag==0){
			//caclculations of misses
			unsigned int blockaddress=parse(address,*cache,BLOCK_ADDRESS);
			//printf("%u\n",blockaddress);
			// if(adr_spc1[blockaddress]!=1){
				//compulmiss++;
				//adr_spc1[blockaddress]=1;
			//}
			
			//end of calculations	
			
			for(int i=0;i<cache->assoc;i++){
				if(cache->cache_set[set].block[i].LRU==0){
					
					cache->cache_set[set].block[i].LRU=cache->assoc-1;
					cache->cache_set[set].block[i].valid=1;	//moving block from memory
					cache->cache_set[set].block[i].tag=TAG;
					cache->cache_set[set].MRU=i;		//updating MRU
					for(int j=0;j<cache->assoc-1;j++){
						i++;
						if(i>=cache->assoc)
							i=0;		//loop to udate all LRU values
						if(cache->cache_set[set].block[i].LRU>0)
							cache->cache_set[set].block[i].LRU--;
					}
					break;	
				}
			}
				
		}
			tni=tni+1;
	}
	cache->TNi=tni;
	cache->PHR=ph/tni;
	int misses=tni-cache->hits;
	//printf("\nCompulsory misses:: %d\n",compulmiss);
	//printf("Conflict misses:: %d\n",misses-compulmiss);
	//printf("Capacitive misses:: %d\n",capmiss);
	printf("Prediction hit rate::  %f\n",cache->PHR);
	printf("Prediction hit :: %f\n",ph);
	printf("Number of ways opened on average :: %f\n",nwo/cache->TNi);
	printf("prediction miss (cache hit):: %d\n",pmch);
	printf("Number of misses::  %d\nNumber of hits::   %d\n",misses,cache->hits);
	printf("Number of instructions:: %d\n",cache->TNi);
	//free(adr_spc1);
}

void read_whcache(FILE* fp,Cache* cache){	
	int i,j,flag=0;
	float nwo=0;
	cache->hits=0;
	cache->TNi=0;
	unsigned int address,TAG,set;
	int compulmiss=0;
	way_halting_array* wha=malloc((cache->cache_size/cache->block_size)*sizeof(way_halting_array));
	//char* adr_spc1=malloc((cache->cache_size/(cache->block_size*8))*sizeof(char));
	int* adr_spc1=malloc(((double)(pow(2,32)/cache->block_size))*sizeof(int));
	//printf("%f\n",pow(2,32)/cache->block_size);
	//variables for calculations
	int n0=0,n1=0,n2=0,n3=0,n4=0,nm=0;
	int counter=0;
	while(1){
		flag=0;
		fscanf(fp,"%x",&address);
		if(feof(fp))break;				
		set=parse(address,*cache,INDEX);
		TAG=parse(address,*cache,_TAG);
		counter=0;
		for(i=0;i<(cache->cache_size/cache->block_size);i++){
			if(wha[i].array==(TAG&15)){
				wha[i].enable=1;		//word line of this block is enabled
			}
		}
		//partial comparison and indexing
		for(i=0;i<cache->assoc;i++){
			if(wha[i+set*cache->assoc].enable==1){
				nwo++;
				counter++;
				if(TAG==cache->cache_set[set].block[i].tag && cache->cache_set[set].block[i].valid==1){
					cache->hits++;
					flag=1;
					if(cache->cache_set[set].block[i].LRU!=cache->assoc-1){
						cache->cache_set[set].block[i].LRU=cache->assoc-1;
						for(int j=0;j<cache->assoc-1;j++){
							i++;
							if(i>=cache->assoc)
								i=0;
							if(cache->cache_set[set].block[i].LRU>0)
								cache->cache_set[set].block[i].LRU--;
						}
					}
					//break;
					
				}
			}
		}
		if(flag==0){
			unsigned int blockaddress=parse(address,*cache,BLOCK_ADDRESS);
			//if(adr_spc1[blockaddress]!=1){
				//compulmiss++;
				//adr_spc1[blockaddress]=1;
			//}
			for(int i=0;i<cache->assoc;i++){
				if(cache->cache_set[set].block[i].LRU==0){
					
					cache->cache_set[set].block[i].LRU=cache->assoc-1;
					cache->cache_set[set].block[i].valid=1;	//moving block from memory
					cache->cache_set[set].block[i].tag=TAG;
					wha[i+(set)*cache->assoc].array=(TAG&15);
					cache->cache_set[set].MRU=i ;		//updating MRU
					for(int j=0;j<cache->assoc-1;j++){
						i++;
						if(i>=cache->assoc)
							i=0;		//loop to update all LRU values
						if(cache->cache_set[set].block[i].LRU>0)
							cache->cache_set[set].block[i].LRU--;
					}
					break;	
				}
			}
		}	
		for(i=0;i<(cache->cache_size/cache->block_size);i++){
			wha[i].enable=0;
		}	
		cache->TNi++;
		switch(counter){
		case 0: n0++;break;
		case 1: n1++;break;
		case 2: n2++;break;
		case 3: n3++;break;
		case 4: n4++;break;
		default:nm++;break;
		}
		
	}
	//printf("Number of compulsory misses:: %d\nNumber of conflict misses:: %d\n\n",compulmiss,cache->TNi-cache->hits-compulmiss);
	//printf("Number of times\n0 ways opened:: %d\n1 way opened:: %d\n2 ways opened:: %d\n3 ways opened:: %d\n4 ways opened:: %d\n",
	printf("Number of ways opened on average:: %f\n",nwo/cache->TNi);
	printf("Number of misses:: %d\n",cache->TNi-cache->hits);
	printf("Number of hits:: %d\n",cache->hits);
	printf("Number of instructions:: %d\n",cache->TNi);
	//n0,n1,n2,n3,n4);

}	
		
	
