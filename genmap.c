#define BUILD_TILE_BUILDER_IMPLEMENTATION
#include"btb.h"

#define map_width 8
#define map_height 8
#define version_num

btb_map_t map[map_height * map_width] = {
        3,0,0,1,1,0,0,3,
        0,0,0,1,1,0,0,0,
        0,0,1,0,1,0,0,0,
        0,0,1,0,1,0,0,0,
        0,1,0,0,1,0,0,0,
        1,1,1,1,1,1,1,1,
        0,0,0,0,1,0,0,0,
        3,0,0,0,1,0,0,3
};

btb_map_t map2[map_height * map_width] = {
        3,0,0,0,1,0,0,3,
        0,0,0,0,1,0,0,0,
        0,0,0,0,1,0,0,0,
        0,0,0,0,1,0,0,0,
        0,0,0,0,1,0,0,0,
        1,1,1,1,1,1,1,1,
        0,0,0,0,1,0,0,0,
        3,0,0,0,0,0,0,3
};

btb_head_data hd = {
    .width     = map_width,
    .height    = map_height,
    .info      = "ver0.1.0",
    .page = 2
};


/* void writemap(void *pages [],uint8_t pagenum,FILE *fp){ */
/*     for(int p = 0;p < pagenum;p++){ */
/*         btb_map_t *mapptr = pages[p]; */
/*         fwrite(mapptr,sizeof(btb_map_t),map_width * map_height,fp); */
/*     } */
/* } */

int main(){
    FILE *fp = NULL;
    fp = fopen("./the4.btb","wb");
    /* fwrite(&hd,sizeof(hd),1,fp); */

    printf("size:%zu\n",sizeof(btb_head_data) + sizeof(map) + sizeof(map2));

    btb_mapwrite((btb_map_t *[]){map,map2},hd,fp);
    
    fclose(fp);

    return 0;
}


