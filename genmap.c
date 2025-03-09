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

int16_t map2[map_height][map_width] = {
		{-1,0,0,0,1,0,0,-1},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{1,1,1,1,1,1,1,1},
		{0,0,0,0,1,0,0,0},
		{-1,0,0,0,0,0,0,-1}
};

head_data hd = {
	.width     = map_width,
	.height    = map_height,
	.info      = "ver0.1.0"
};

uint8_t pagenum = 1;
tile_byte_num et[] = {
	{0,1,3,0}
};

/* void writemap_p1(void *pages [],uint8_t pagenum,tile_byte_num et[],FILE *fp){ */
/* 	for(int p = 0;p <= pagenum;p++){ */
/* 		uint8_t tile_size = extra_tile_get(et,p) + 1; */
/* 		void *mapptrD = pages[p],*mapptr = pages[p]; */
/* 		fwrite(mapptrD,tile_size,1,fp); */
/* 	for(int i = 1;i < map_width * map_height;i++){ */
		
/* 	} */
/* 	} */
/* } */

void writemap(void *pages [],uint8_t pagenum,tile_byte_num et[],FILE *fp){
	for(int p = 0;p <= pagenum;p++){
		uint8_t tile_size = tile_byte_get(et,p) + 1;
		void *mapptr = pages[p];
	for(int i = 0;i < map_width * map_height;i++){
		fwrite((mapptr + (i * tile_size)),tile_size,1,fp);
	}
	}
}

int main(){
	printf("hd size:%zu\n",sizeof(head_data));
	FILE *fp = NULL;
	fp = fopen("./the4.btb","wb");
	fwrite(&hd,sizeof(head_data),1,fp);

	/* printf("et = %d\n",*((uint8_t *)(&et))); */
	/* fputc(pagenum,fp); */
	fwrite(&pagenum,sizeof(pagenum),1,fp);
	/* fputc(*((uint8_t *)(&et)),fp); */
	uint8_t Z = ((pagenum + 1) / 4) + 1;
	fwrite(et,sizeof(tile_byte_num),Z,fp);

	writemap((void *[]){map,map2},pagenum,et,fp);
	/* for(int y = 0;y < map_height;y++) */
	/* for(int x = 0;x < map_width;x++){ */
	/* 	uint8_t data = map[y][x]; */
	/* 	fputc(data,fp); */
	/* } */

	/* for(int y = 0;y < map_height;y++) */
	/* for(int x = 0;x < map_width;x++){ */
	/* 	uint16_t data = map2[y][x]; */
	/* 	fputc(data,fp); */
	/* } */
	
	fclose(fp);

	return 0;
}
