#ifndef BUILD_TILE_BUILDER
#define BUILD_TILE_BUILDER
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

/* max to 2^16 x 2^16*/

typedef uint64_t btb_info_len_t;
typedef char* btb_info_t;
typedef uint16_t btb_mapcell_t;
typedef uint16_t btb_side_len_t;
typedef uint8_t  btb_pagenum_t;

typedef struct{
    btb_mapcell_t *data;
}btb_map_t;

typedef struct{
    btb_info_len_t info_size;
    btb_info_t     info;
    btb_map_t      *maps;
    btb_mapcell_t  *data;
    btb_side_len_t width;
    btb_side_len_t height;
    btb_pagenum_t  pagenum;
}btb_data_t;

/* void btb_mapwrite(btb_mapcell_t **mapdata,btb_head_data hd,void *info,size_t info_size,FILE *fp); */
void btb_mapwrite(btb_data_t src,FILE *fp);
/* void btb_mapread(btb_head_data *hd,void **info,btb_mapcell_t ***mapdata,FILE *fp); */
void btb_mapread(btb_data_t *dest,FILE *fp);

#ifdef BUILD_TILE_BUILDER_IMPLEMENTATION_W

void btb_mapwrite(btb_data_t src,FILE *fp){
    if(src.info == NULL || src.info_size == 0){
        btb_info_len_t z = 0;
        fwrite(&(z),sizeof(z),1,fp);
    }
    else{
        fwrite(&(src.info_size),sizeof(src.info_size),1,fp);
        fwrite(src.info,src.info_size,1,fp);
    }
    fwrite(&(src.width),sizeof(src.width) * 2 + sizeof(src.pagenum),1,fp);
    for(int p = 0;p < src.pagenum;p++){
        fwrite(src.maps[p].data,sizeof(src.maps[0].data[0]),src.width * src.height,fp);
    }
}

#endif//BUILD_TILE_BUILDER_IMPLEMENTATION_W

#ifdef  BUILD_TILE_BUILDER_IMPLEMENTATION_R

void btb_mapread(btb_data_t *dest,FILE *fp){
    fread(dest->info_size,sizeof(dest.info_size),1,fp);
    /* printf("z: %zu\n",z); */
    dest->info = malloc(dest->info_size);
    fread(dest->info,dest->info_size,1,fp);
    fread(dest->width,sizeof(data->width) * 2 + sizeof(data->pagenum),1,fp);
    dest->maps = malloc(sizeof(dest->maps[0]) * dest->pagenum);
    dest->data = malloc(sizeof(dest->maps[0].data[0]) * dest->pagenum);
    for(btb_pagenum_t i = 0;i < pagenum;i++)
        dest->maps[i] =dest->data + i * dest->width * dest->height;
    fread(dest->data,sizeof(dest->maps[0].data[0]),dest->width * dest->height,fp);
}

#endif//BUILD_TILE_BUILDER_IMPLEMENTATION_R

#endif//BUILD_TILE_BUILDER
