#include"btb.h"

#define map_width 8
#define map_height 8
#define version_num

uint8_t map[map_height][map_width] = {
	{0,0,0,1,1,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,1,0,1,0,0,0},
	{0,0,1,0,1,0,0,0},
	{0,1,0,0,1,0,0,0},
	{1,1,1,1,1,1,1,1},
	{0,0,0,0,1,0,0,0},
	{0,0,0,0,1,0,0,0}
};

head_data hd = {
	.version1  = 0,
	.version2  = 1,
	.version3  = 0,
	.width     = map_width,
	.height    = map_height,
	.tile_size = 0
};

int main(){
	FILE *fp = NULL;
	fp = fopen("./the4.btb","wb");
	for(size_t i = 0;i < sizeof(head_data);i++){
		/* printf("%x\n",); */
		fputc(((char *)(&hd))[i],fp);
	}
	
	fclose(fp);

	return 0;
}
