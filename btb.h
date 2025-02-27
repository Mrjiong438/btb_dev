#ifndef BUILD_TILE_BUILDER
#define BUILD_TILE_BUILDER 1

#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>

typedef struct{
	uint16_t width;
	uint16_t height;
	char info[16];
}head_data;

typedef struct{
	uint8_t n1 : 2;
	uint8_t n2 : 2;
	uint8_t n3 : 2;
	uint8_t n4 : 2;
}extra_tile;

typedef union{
	uint32_t u32;
	uint16_t u16;
	uint8_t  u8;
}tile_data;

uint8_t get_tile_size(extra_tile list[],uint8_t page){
	uint8_t r;
	switch(page % 4){
		case 0:
			r = list[page / 4].n1;
			break;
		case 1:
			r = list[page / 4].n2;
			break;
		case 2:
			r = list[page / 4].n3;
			break;
		case 3:
			r = list[page / 4].n4;
			break;
	}
	return r+1;
}
uint8_t extra_tile_get(extra_tile list[],uint8_t page){
	uint8_t r;
	switch(page % 4){
		case 0:
			r = list[page / 4].n1;
			break;
		case 1:
			r = list[page / 4].n2;
			break;
		case 2:
			r = list[page / 4].n3;
			break;
		case 3:
			r = list[page / 4].n4;
			break;
	}
	return r;
}

#endif//BUILD_TILE_BUILDER
