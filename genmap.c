#define BUILD_TILE_BUILDER_IMPLEMENTATION_W
#include"btb.h"

#define map_width 8
#define map_height 8
#define version_num

uint16_t map_s[map_height * map_width] = {
    3,0,0,1,1,0,0,3,
    0,0,0,1,1,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,1,0,0,0,0,0,
    0,0,0,0,1,0,0,0,
    1,0,0,1,1,1,0,0,
    0,0,0,0,1,0,0,0,
    3,0,0,0,1,0,0,3
};

uint16_t map2_s[map_height * map_width] = {
    3,0,0,0,1,0,0,3,
    0,0,0,0,1,0,0,0,
    0,0,0,0,1,0,0,0,
    0,0,0,0,1,0,0,0,
    0,0,0,0,1,0,0,0,
    1,1,1,1,1,1,1,1,
    0,0,0,0,1,0,0,0,
    3,0,0,0,0,0,0,3
};




int main(){

    btb_mapcell_t map[map_height * map_width] = {0};
    btb_mapcell_t map2[map_height * map_width] = {0};

    for(unsigned int i = 0;i < map_width * map_height;i++){
        map[i].id = map_s[i];
        map2[i].id = map2_s[i];
    }

    btb_map_t
    m1 = {
        .data = map
    },
    m2 = {
        .data = map2
    };

    btb_map_t maplist[2] = {m1,m2};

    btb_data_t data = {
        .width     = map_width,
        .height    = map_height,
        .pagenum = 2,
        .info_size = 3,
        .info = "ve",
        .maps = maplist
    };

    /* for(uint8_t i = 0;i < 8;i++) */
    /*     printf("%d",data.maps[1].data[i]); */
    printf("btb_data_t:%zu\n",sizeof(btb_data_t));
    printf("btb_mapcell_t:%zu\n",sizeof(btb_mapcell_t));
    /* FILE *fp = NULL; */
    /* fp = fopen("./the4.btb","wb"); */
    btb_mapwrite(data,"./the4.btb");

    /* fclose(fp); */

    return 0;
}
