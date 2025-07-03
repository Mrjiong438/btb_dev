#ifndef BUILD_TILE_BUILDER
#define BUILD_TILE_BUILDER
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

typedef struct{         /* max to 2^16 x 2^16*/
	char     info[64];
	uint16_t width;
	uint16_t height;
        uint8_t  page;
}btb_head_data;

typedef int16_t btb_map_t;
void btb_mapwrite(btb_map_t **mapdata,btb_head_data hd,FILE *fp);
void btb_mapread(btb_head_data *hd,btb_map_t ***mapdata,FILE *fp);

#ifdef BUILD_TILE_BUILDER_IMPLEMENTATION

void btb_mapwrite(btb_map_t **mapdata,btb_head_data hd,FILE *fp){
    fwrite(&hd,sizeof(hd),1,fp);
    for(int p = 0;p < hd.page;p++){
        btb_map_t *mapptr = mapdata[p];
        fwrite(mapptr,sizeof(*mapptr),hd.width * hd.height,fp);
    }
}

void btb_mapread(btb_head_data *hd,btb_map_t ***mapdata,FILE *fp){
    fread(hd,sizeof(*hd),1,fp);
    *mapdata = malloc(sizeof((**mapdata)) * hd->page);
    for(uint8_t i = 0;i < hd->page;i++){
        (*mapdata)[i] = malloc(sizeof(***mapdata) * hd->width * hd->height);
        fread((*mapdata)[i],sizeof(***mapdata),hd->width * hd->height,fp);
    }
}

#endif//BUILD_TILE_BUILDER_IMPLEMENTATION
#endif//BUILD_TILE_BUILDER
