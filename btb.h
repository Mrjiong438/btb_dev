#ifndef BUILD_TILE_BUILDER
#define BUILD_TILE_BUILDER 1

#include<stdio.h>
#include<stdint.h>

typedef struct {
	uint32_t version1  : 10;
	uint32_t version2  : 10;
	uint32_t version3  : 10;
	uint32_t tile_size : 2;
	uint16_t width;
	uint16_t height;
}head_data;

#endif//BUILD_TILE_BUILDER
