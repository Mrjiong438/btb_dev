#include"btb.h"

int main(int argc,char *argv[]){
	if(argc < 2){
		fprintf(stderr,"no input\n");
		return -1;
	}
	FILE *fp = fopen(argv[1],"rb");
	if(fp == NULL){
		fprintf(stderr,"open file fail\n");
		return -1;
	}

	head_data hd;
	fread(&hd,8,1,fp);

	printf(
			"version: %u.%u.%u\n"
			"tile size: %u\n"
			"map size: %ux%u\n",
			hd.version1,
			hd.version2,
			hd.version3,
			hd.tile_size,
			hd.width,
			hd.height
	);

	return 0;
}
