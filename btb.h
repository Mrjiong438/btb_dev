#ifndef BUILD_TILE_BUILDER
#define BUILD_TILE_BUILDER 1

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

typedef struct{
	uint32_t version1  : 10;
	uint32_t version2  : 10;
	uint32_t version3  : 12;
	uint16_t width;
	uint16_t height;
}head_data;

typedef struct{
	uint8_t n1 : 2;
	uint8_t n2 : 2;
	uint8_t n3 : 2;
	uint8_t n4 : 2;
}extra_tile;

#endif//BUILD_TILE_BUILDER
