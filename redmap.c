#include"btb.h"

void readmap(FILE *fp);

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
	fread(&hd,sizeof(head_data),1,fp);

	printf(
			"version: %u.%u.%u\n"
			"map size: %ux%u\n",
			hd.version1,
			hd.version2,
			hd.version3,
			hd.width,
			hd.height
	);

	uint8_t pages;
	fread(&pages,sizeof(uint8_t),1,fp);
	printf("pages:%d\n",pages);

	uint8_t extbyte = (pages/4)+1;
	extra_tile *extlist = NULL;
	extlist = malloc(sizeof(extra_tile) * (extbyte));
	fread(extlist,sizeof(extra_tile),extbyte,fp);
	for(int i = 0;i < extbyte;i++)
		printf("%d %d %d %d\n",extlist[i].n1,extlist[i].n2,extlist[i].n3,extlist[i].n4);

	//read map
	void *mapdata[2] = {0};
	mapdata[0] = malloc(sizeof(uint8_t) * hd.width * hd.height);
	fread(mapdata[0],sizeof(uint8_t) * hd.width * hd.height,1,fp);

	for(int y = 0;y < hd.height;y++){
	for(int x = 0;x < hd.height;x++){
		int8_t *tile = mapdata[0] + (y * hd.width) + x;
		if(*tile < 0){
			printf("X");
			continue;
		}
		switch(*tile){
			case 0:
				printf(" ");
				break;
			default:
				printf("%d",*tile);
				break;
		}
	}
		printf("\n");
	}

	fclose(fp);

	return 0;
}
