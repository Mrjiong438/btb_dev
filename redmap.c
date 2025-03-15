#include"btb.h"

void readmap(FILE *fp);
void printmap(void *mapdata,uint16_t width,uint16_t height,uint8_t size);
uint32_t mapvalue(void *mapdata,size_t index,uint8_t size);

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
			"info: %s\n"
			"map size: %ux%u\n",
			hd.info,
			hd.width,
			hd.height
	);

	uint8_t pages;
	fread(&pages,sizeof(uint8_t),1,fp);
	printf("pages:%d\n",pages);

	uint8_t extbyte = (pages/4)+1;
	tile_byte_num *extlist = NULL;
	extlist = malloc(sizeof(*extlist) * (extbyte));
	fread(extlist,sizeof(*extlist),extbyte,fp);
	/* for(int i = 0;i < extbyte;i++) */
	/* 	printf("%d %d %d %d\n",extlist[i].n1,extlist[i].n2,extlist[i].n3,extlist[i].n4); */
	for(int i = 0;i <= pages;i++)
		printf("%d ",tile_byte_get(extlist,i));
	printf("\n");

	//read map
	void *mapdata[2] = {0};
	for(int i = 0;i < pages;i++){
		mapdata[i] = malloc((tile_byte_get(extlist,i) + 1) * sizeof(uint8_t) * hd.width * hd.height);
		fread(mapdata[i],sizeof(uint8_t) * hd.width * hd.height,tile_byte_get(extlist,i) + 1,fp);
		/* printmap(mapdata[i],hd.width,hd.height,tile_byte_get(extlist,i)); */
	}

	fclose(fp);

	return 0;
}

void readmap(FILE *fp);
void printmap(void *mapdata,uint16_t width,uint16_t height,uint8_t size){
	for(int y = 0;y < height;y++){
	for(int x = 0;x < width;x++){
		/* uint32_t tile = mapdata + (y * width) + x; */
		uint32_t tile = mapvalue(mapdata,(y * width) + x,size);
		switch(tile){
			case 0:
				printf(" ");
				break;
			case 3:
				printf("X");
				break;
			default:
				printf("%u",tile);
				break;
		}
	}
		printf("\n");
	}
}

uint32_t mapvalue(void *mapdata,size_t index,uint8_t size){
	uint32_t r;
	switch(size){
		case 0:
			r = ((uint8_t *)mapdata)[index];
			break;
		case 1:
			r = ((uint16_t *)mapdata)[index];
			break;
		case 2:
			r = ((uint32_t *)mapdata)[index];
			break;
		case 3:
		default:
			break;
	}
	return r;
}
