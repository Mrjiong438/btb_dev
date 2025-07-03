#ifndef BUILD_TILE_BUILDER
#define BUILD_TILE_BUILDER 1

#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>

typedef struct{         /* max to 2^16 x 2^16*/
	char     info[64];
	uint16_t width;
	uint16_t height;
        uint8_t  page;
}head_data;

typedef int16_t mapsize_t;

#endif//BUILD_TILE_BUILDER
