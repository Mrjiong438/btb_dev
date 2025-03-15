#include"btb.h"

#define map_width 8
#define map_height 8
#define version_num

//TODO write by size

int32_t map[map_height][map_width] = {
		{3,0,0,1,1,0,0,3},
		{0,0,0,1,1,0,0,0},
		{0,0,1,0,1,0,0,0},
		{0,0,1,0,1,0,0,0},
		{0,1,0,0,1,0,0,0},
		{1,1,1,1,1,1,1,1},
		{0,0,0,0,1,0,0,0},
		{3,0,0,0,1,0,0,3}
};

int32_t map2[map_height][map_width] = {
		{3,0,0,0,1,0,0,3},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{1,1,1,1,1,1,1,1},
		{0,0,0,0,1,0,0,0},
		{3,0,0,0,0,0,0,3}
};

head_data hd = {
	.width     = map_width,
	.height    = map_height,
	.info      = "ver0.1.0"
};

uint8_t pagenum = 2;
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

void writemap(void *pages [],uint8_t pagenum,tile_byte_num et[],FILE *fp);

int main(){
	FILE *fp = NULL;
	fp = fopen("./the4.btb","wb");
	fwrite(&hd,sizeof(head_data),1,fp);

	fwrite(&pagenum,sizeof(pagenum),1,fp);
	uint8_t Z = ((pagenum + 1) / 4) + 1;
	fwrite(et,sizeof(tile_byte_num),Z,fp);
	printf("hd size:%zu\n",sizeof(head_data) + sizeof(tile_byte_num) + 1);

	writemap((void *[]){map,map2},pagenum,et,fp);
	
	fclose(fp);

	return 0;
}

void writemap(void *pages [],uint8_t pagenum,tile_byte_num et[],FILE *fp){
	for(int p = 0;p < pagenum;p++){
		void *mapptr = pages[p];
	for(int i = 0;i < map_width * map_height;i++){
		uint32_t u32;
		uint16_t u16;
		uint8_t u8;
		switch(tile_byte_get(et,p)){
			case 0:
				u8 = (uint8_t)(((uint32_t *)mapptr)[i]);
				fwrite(&u8,sizeof(uint8_t),1,fp);
				break;
			case 1:
				u16 = (uint16_t)(((uint32_t *)mapptr)[i]);
				fwrite(&u16,sizeof(uint16_t),1,fp);
				break;
			case 2:
				u32 = (uint32_t)(((uint32_t *)mapptr)[i]);
				fwrite(&u32,sizeof(uint32_t),1,fp);
				break;
			case 3:
			default:
				break;
		}
	}
	}
}
