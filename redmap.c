#define BUILD_TILE_BUILDER_IMPLEMENTATION_R
#include"btb.h"
#include <stdio.h>

void printmap(btb_map_t map,uint16_t width,uint16_t height){
    putc('\n',stdout);
    for(uint16_t y = 0;y < height;y++){
    for(uint16_t x = 0;x < width;x++){
        switch(map.data[x + y * width]){
            case 0:
                printf(" ");
                break;
            case 3:
                printf("X");
                break;
            default:
                printf("%u",map.data[x + y * width]);
                break;
        }
    }
        printf("\n");
    }
}

int main(int argc,char *argv[]){
    if(argc < 2){
        fprintf(stderr,"no input\n");
        return -1;
    }
    FILE *fp = fopen(argv[1],"rb");
    if(fp == NULL){
        fprintf(stderr,"open file fail\n");
        return -1;
    }
    btb_data_t mapdata = {0};

    btb_mapread(&mapdata,fp);
    fclose(fp);

    printf("info: %s\n",mapdata.info);
    /* for(unsigned int i = 0;i < 9;i++){ */
    /*     putchar(info[i]); */
    /* } */
    printf("map size: %ux%u\n",mapdata.width,mapdata.height);
    printf("pagenum: %u\n",mapdata.pagenum);

    for(int i = 0;i < mapdata.pagenum;i++){
        printmap(mapdata.maps[i],mapdata.width,mapdata.height);
    }

    return 0;
}

