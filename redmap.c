#define BUILD_TILE_BUILDER_IMPLEMENTATION
#include"btb.h"
#include <stdio.h>

/* void mapread(btb_head_data *hd,btb_map_t ***mapdata,FILE *fp){ */
/*     fread(hd,sizeof(btb_head_data),1,fp); */
/*     *mapdata = malloc(sizeof((**mapdata)) * hd->page); */
/*     for(uint8_t i = 0;i < hd->page;i++){ */
/*         (*mapdata)[i] = malloc(sizeof(***mapdata) * hd->width * hd->height); */
/*         fread((*mapdata)[i],sizeof(***mapdata),hd->width * hd->height,fp); */
/*     } */
/* } */

void printmap(btb_map_t *mapdata,uint16_t width,uint16_t height){
    putc('\n',stdout);
    for(uint16_t y = 0;y < height;y++){
    for(uint16_t x = 0;x < width;x++){
        switch(mapdata[x + y * width]){
            case 0:
                printf(" ");
                break;
            case 3:
                printf("X");
                break;
            default:
                printf("%u",mapdata[x + y * width]);
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

    btb_head_data hd = {0};
    btb_map_t **mapdata = NULL;
    btb_mapread(&hd,&mapdata,fp);
    fclose(fp);

    printf(
            "info: %s\n"
            "map size: %ux%u\n"
            "pagenum: %u\n",
            hd.info,
            hd.width,
            hd.height,
            hd.page
    );

    for(int i = 0;i < hd.page;i++){
        printmap(mapdata[i],hd.width,hd.height);
    }


    return 0;
}

