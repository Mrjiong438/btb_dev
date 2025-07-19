#ifndef BUILD_TILE_BUILDER
#define BUILD_TILE_BUILDER
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

typedef struct{         /* max to 2^16 x 2^16*/
    uint16_t width;
    uint16_t height;
    uint8_t  page;
}btb_head_data;

typedef int16_t btb_map_t;
void btb_mapwrite(btb_map_t **mapdata,btb_head_data hd,void *info,size_t info_size,FILE *fp);
void btb_mapread(btb_head_data *hd,void **info,btb_map_t ***mapdata,FILE *fp);

#ifdef BUILD_TILE_BUILDER_IMPLEMENTATION_W

void btb_mapwrite(btb_map_t **mapdata,btb_head_data hd,void *info,size_t info_size,FILE *fp){
    fwrite(&hd,sizeof(hd),1,fp);
    if(info == NULL){
        size_t z = 0;
        fwrite(&(z),sizeof(z),1,fp);
    }
    else{
        fwrite(&info_size,sizeof(info_size),1,fp);
        fwrite(info,1,info_size,fp);
    }
    for(int p = 0;p < hd.page;p++){
        btb_map_t *mapptr = mapdata[p];
        fwrite(mapptr,sizeof(*mapptr),hd.width * hd.height,fp);
    }
}

#endif//BUILD_TILE_BUILDER_IMPLEMENTATION_W

#ifdef BUILD_TILE_BUILDER_IMPLEMENTATION_R

void btb_mapread(btb_head_data *hd,void **info,btb_map_t ***mapdata,FILE *fp){
    fread(hd,sizeof(*hd),1,fp);
    size_t z;
    fread(&z,sizeof(z),1,fp);
    /* printf("z: %zu\n",z); */
    *info = malloc(z);
    fread(*info,z,1,fp);
    *mapdata = malloc(sizeof((**mapdata)) * hd->page);
    for(uint8_t i = 0;i < hd->page;i++){
        (*mapdata)[i] = malloc(sizeof(***mapdata) * hd->width * hd->height);
        fread((*mapdata)[i],sizeof(***mapdata),hd->width * hd->height,fp);
    }
}

#endif//BUILD_TILE_BUILDER_IMPLEMENTATION_R
#endif//BUILD_TILE_BUILDER
