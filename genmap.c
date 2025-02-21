#include"btb.h"

#define map_width 8
#define map_height 8
#define version_num

int8_t map[map_height][map_width] = {
		{-1,0,0,1,1,0,0,-1},
		{0,0,0,1,1,0,0,0},
		{0,0,1,0,1,0,0,0},
		{0,0,1,0,1,0,0,0},
		{0,1,0,0,1,0,0,0},
		{1,1,1,1,1,1,1,1},
		{0,0,0,0,1,0,0,0},
		{-1,0,0,0,1,0,0,-1}
};

head_data hd = {
	.version1  = 0,
	.version2  = 1,
	.version3  = 0,
	.width     = map_width,
	.height    = map_height,
};

uint8_t pages = 1;
extra_tile et = {0,0,3,0};

int main(){
	printf("hd size:%zu\n",sizeof(head_data));
	FILE *fp = NULL;
	fp = fopen("./the4.btb","wb");
	for(size_t i = 0;i < sizeof(head_data);i++){
		/* printf("%x\n",); */
		fputc(((char *)(&hd))[i],fp);
	}

	/* printf("et = %d\n",*((uint8_t *)(&et))); */
	fputc(pages,fp);
	fputc(*((uint8_t *)(&et)),fp);

	for(int y = 0;y < map_height;y++)
	for(int x = 0;x < map_width;x++){
		uint8_t data = map[y][x];
		fputc(data,fp);
	}
	
	fclose(fp);

	return 0;
}
