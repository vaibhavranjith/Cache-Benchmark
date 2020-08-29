
typedef struct {
	unsigned int valid;
	unsigned int tag;
	unsigned int dirty;
	char *line;
	unsigned int LRU;
}Block;

typedef struct {
	int MRU;
	Block *block ;
}Cache_set;

typedef struct {
	int cache_size;
	int block_size;
	int assoc;
	int hits;
	int TNi;
	float PHR;	
	Cache_set *cache_set ;
}Cache;
typedef struct{
	int array;
	int enable;
}way_halting_array;	
int create_cache(Cache*);	//creates cache
unsigned int parse(unsigned int,Cache,int);
void print_cache(Cache);
void read_wpcache(FILE*,Cache*);
void read_whcache(FILE*,Cache*);	
void read_cnvcache(FILE*,Cache*);
