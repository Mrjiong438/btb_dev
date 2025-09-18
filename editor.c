#define CLAY_IMPLEMENTATION
#include"clay.h"
#include<stdio.h>
#include<stdint.h>
#include"raylib.h"
#include"renderers/clay_renderer_raylib.c"

#define COLOR_DARK  {109,128,181,255}
/* #define COLOR_LIGHT {248,248,255,255} */
#define COLOR_LIGHT {176,196,222,255}
#define COLOR_BACK  {47,79,79,255}
/* #define final_size_block (size_block * map_view_data.customData.map_view.zoom) */
/* const uint8_t size_block = 16; */

void HandleClayErrors(Clay_ErrorData errorData) {
    // See the Clay_ErrorData struct for more information
    printf("%s", errorData.errorText.chars);
}

uint16_t monitor_n;
uint16_t monitor_w;
uint16_t monitor_h;
uint16_t window_w;
uint16_t window_h;
btb_data_t current_map;

Vector2 mouse_position;
Vector2 mouse_position_last;
#define MAP_ZOOM (map_view_data.customData.map_view.zoom)
#define TILE_ZOOM (tile_view_data.customData.map_view.zoom)
Vector2 whell_delta;
MouseCursor cursor_state;
CustomLayoutElement map_view_data;
CustomLayoutElement tile_view_data;

typedef enum {
    drag_dir_Hf,
    drag_dir_Vf,
    drag_dir_Hu,
    drag_dir_Vu
}drag_dir_t;
//H and V for horizontal and vertical
//f and u for float and uint16

typedef enum {
    drag_side_postive = 1,
    drag_side_negtive = -1,
}drag_element_side_t;//top to botton, left to right is postive

bool dragging = false;
drag_dir_t dragging_dir;
drag_element_side_t drag_side;
uint16_t drag_limit;

float temp_size;
Clay_ElementId temp_elementid;
Clay_ElementData temp_elementdata;
float *targit_size = NULL;
float width_side_bar = 250;
float height_tiles_percent = 0.5f;

/* int64_t block_point_at; */
#define bpa_map (map_view_data.customData.map_view.block_point_at)

void update_drag_size(){
    switch(dragging_dir){
        case drag_dir_Vu:
            temp_size = *targit_size + drag_side * (mouse_position.y - mouse_position_last.y);
        break;
        case drag_dir_Hu:
            temp_size = *targit_size + drag_side * (mouse_position.x - mouse_position_last.x);
        break;
        case drag_dir_Vf:
            temp_size = *targit_size * drag_limit + drag_side * (mouse_position.y - mouse_position_last.y);
        break;
        case drag_dir_Hf:
            temp_size = *targit_size * drag_limit + drag_side * (mouse_position.x - mouse_position_last.x);
        break;
    }
    /* printf("%f,%f,%d\n",height_tiles_percent,temp_size,drag_limit); */
    switch(dragging_dir){
        case drag_dir_Vu:
        case drag_dir_Hu:
            if     (temp_size < 0){
                *targit_size = 0;
            }
            else if(temp_size > drag_limit){
                *targit_size = drag_limit;
            }
            else
                *targit_size = temp_size;
        break;
        case drag_dir_Vf:
        case drag_dir_Hf:
            if     (temp_size < 0){
                *targit_size = 0;
            }
            else if(temp_size > drag_limit - 10){
                *targit_size = (float)(drag_limit - 10) / drag_limit;//10 as bar width
            }
            else
                *targit_size = temp_size / drag_limit;
        break;
    }
}

void layout_code(){
            CLAY({
                .id = CLAY_ID("container_outer"),
                .layout = { 
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                        .height = CLAY_SIZING_GROW(0)
                    },
                    /* .padding = CLAY_PADDING_ALL(16), */
                    /* .childGap = 16, */
                    .layoutDirection = CLAY_TOP_TO_BOTTOM
                },
                .backgroundColor = COLOR_DARK
            }){
                CLAY({
                    .id = CLAY_ID("header_bar"),
                    .backgroundColor = COLOR_LIGHT,
                    .border = {
                        .width = {
                            5,
                            5,
                            5,
                            5
                        },
                        .color = {0,0,0,255}
                    },
                    .layout = {
                        .sizing = {
                            .width = CLAY_SIZING_GROW(0),
                            .height = CLAY_SIZING_FIXED(60)
                        },
                    }
                }){}
                CLAY({
                    .id = CLAY_ID("container_lower"),
                    .layout = {
                        .sizing = {
                            .width = CLAY_SIZING_GROW(0),
                            .height = CLAY_SIZING_GROW(0)
                        }
                    }
                }){
                    /* CLAY({ */
                    /*     .id = CLAY_ID("bar_left"), */
                    /*     .layout = { */
                    /*         .sizing = { */
                    /*             .width = CLAY_SIZING_FIXED(250), */
                    /*             .height = CLAY_SIZING_GROW(0) */
                    /*         } */
                    /*     }, */
                    /*     .backgroundColor = COLOR_LIGHT */
                    /* }){} */
                    CLAY({
                        .id = CLAY_ID("map_view_container"),
                        .layout = {
                            .sizing = {
                                .width = CLAY_SIZING_GROW(0),
                                .height = CLAY_SIZING_GROW(0)
                            },
                            .padding = CLAY_PADDING_ALL(10)
                        }
                    }){
                        CLAY({
                            .id = CLAY_ID("map_view"),
                            .custom = {.customData = &map_view_data},
                            /* .border = { */
                            /*     .width = CLAY_BORDER_OUTSIDE(10), */
                            /*     .color = COLOR_DARK */
                            /* }, */
                            .layout = {
                                .sizing = {
                                    .width = CLAY_SIZING_GROW(0),
                                    .height = CLAY_SIZING_GROW(0)
                                }
                            }
                        }){}
                    }
                    CLAY({
                        .id = CLAY_ID("drag_map_view"),
                        .backgroundColor = {0,0,0,255},
                        .layout = {
                            .sizing = {
                                .width = CLAY_SIZING_FIXED(10),
                                .height = CLAY_SIZING_GROW(0)
                            }
                        }
                    }){
                        /* if(Clay_Hovered()) */
                        /*     cursor_state = MOUSE_CURSOR_RESIZE_EW; */
                    }
                    CLAY({
                        .id = CLAY_ID("side_bar"),
                        /* .border = { */
                        /*     .width = CLAY_BORDER_OUTSIDE(5), */
                        /*     .color = {0,0,0,255} */
                        /* }, */
                        /* .backgroundColor = COLOR_LIGHT, */
                        .layout = {
                            .layoutDirection = CLAY_TOP_TO_BOTTOM,
                            .sizing = {
                                .width = CLAY_SIZING_FIXED(width_side_bar),
                                .height = CLAY_SIZING_GROW(0)
                            }
                        }
                    }){
                        CLAY({
                            .id = CLAY_ID("tiles"),
                            .backgroundColor = COLOR_LIGHT,
                            .layout = {
                                .sizing = {
                                    .width = CLAY_SIZING_GROW(0),
                                    .height = CLAY_SIZING_PERCENT(height_tiles_percent)
                                }
                            }
                        }){
                            CLAY({
                                .id = CLAY_ID("tile_view"),
                                .custom = {.customData = &tile_view_data},
                                .layout = {
                                    .sizing = {
                                        .width = CLAY_SIZING_GROW(0),
                                        .height = CLAY_SIZING_GROW(0)
                                    }
                                }
                            }){}
                        }
                        CLAY({
                            .id = CLAY_ID("drag_tiles"),
                            .backgroundColor = {0,0,0,255},
                            .layout = {
                                .sizing = {
                                    .width = CLAY_SIZING_GROW(0),
                                    .height = CLAY_SIZING_FIXED(10)
                                }
                            }
                        }){
                            /* if(Clay_Hovered()) */
                            /*     cursor_state = MOUSE_CURSOR_RESIZE_NS; */
                        }
                        CLAY({
                            .id = CLAY_ID("layer"),
                            /* .border = { */
                            /*     .width = CLAY_BORDER_OUTSIDE(5), */
                            /*     .color = {0,0,0,255} */
                            /* }, */
                            .backgroundColor = COLOR_LIGHT,
                            .layout = {
                                .sizing = {
                                    .width = CLAY_SIZING_GROW(0),
                                    .height = CLAY_SIZING_GROW(0)
                                }
                            }
                        }){}
                    }
                }
            }
}

int main(int argc,char* argv[]){
    btb_mapread(&current_map,"./the4.btb");
    map_view_data = (CustomLayoutElement){
        .type = CUSTOM_LAYOUT_ELEMENT_TYPE_MAP_VIEW,
        .customData.map_view = (CustomLayoutElement_map_view){
            .map_data = current_map,
            .block_point_at = UINT64_MAX,
            .x = 0,
            .y = 0,
            .zoom = 1
        }
    };

    uint64_t clay_min_mem = Clay_MinMemorySize();
    /* printf("%ld\n",clay_min_mem); */
    Clay_Arena clay_mem = (Clay_Arena){
        .memory = malloc(clay_min_mem),
        .capacity = clay_min_mem
    };

    SetTargetFPS(120);
    Clay_Raylib_Initialize(0,0,"btb_editor",FLAG_WINDOW_RESIZABLE);
    monitor_n = GetCurrentMonitor();
    monitor_w = GetMonitorWidth(monitor_n);
    monitor_h = GetMonitorHeight(monitor_n);
    window_w = monitor_w * 3 / 4;
    window_h = monitor_h * 3 / 4;
    SetWindowSize(window_w,window_h);
    SetWindowPosition((monitor_w - window_w) / 2,(monitor_h - window_h) / 2);
    /* Clay_Raylib_Initialize(2560,1440,"btb_editor",FLAG_WINDOW_RESIZABLE); */
    /* MaximizeWindow(); */

    Clay_Initialize(
            clay_mem,(Clay_Dimensions){
                .width = GetScreenWidth(),
                .height = GetScreenHeight()
            },
            (Clay_ErrorHandler) { HandleClayErrors, 0}
    );
    /* if((monitor_w / 2) > (monitor_h / 2)) */
    /*     sczoom = (monitor_w / 2); */
    /* else */
    /*     sczoom = (monitor_h / 2); */
    /* ToggleFullscreen(); */
    /* ToggleBorderlessWindowed(); */
    Font fonts[2];
    fonts[0] = LoadFontEx("resources/Roboto-Regular.ttf", 48, 0, 400);
    SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);

    while(!WindowShouldClose()){
        if(IsWindowResized()){
            drag_limit = Clay_GetElementData(Clay_GetElementId(CLAY_STRING("side_bar"))).boundingBox.height;
            temp_size = height_tiles_percent * drag_limit + drag_side * (mouse_position.y - mouse_position_last.y);
            if(temp_size > drag_limit - 10){
                height_tiles_percent = (float)(drag_limit - 10) / drag_limit;//10 as bar width
            }
        }

        mouse_position_last = mouse_position;
        mouse_position = GetMousePosition();
        /* whell_delta = GetMouseWheelMoveV(); */

        //zoom input
#define debug_print_zoom printf("%d\n",map_view_data.customData.map_view.zoom)
        if(IsKeyPressed(KEY_MINUS)){
            debug_print_zoom;
            if(map_view_data.customData.map_view.zoom > 1)
            map_view_data.customData.map_view.zoom--;
        }
        if(IsKeyPressed(KEY_EQUAL)){
            debug_print_zoom;
            map_view_data.customData.map_view.zoom++;
        }

        Clay_SetLayoutDimensions((Clay_Dimensions){
                .width = GetScreenWidth(),
                .height = GetScreenHeight()
        });
        Clay_BeginLayout();
        layout_code();
        Clay_RenderCommandArray clay_rend_cmd = Clay_EndLayout();

        Clay_SetPointerState(
                (Clay_Vector2){mouse_position.x,mouse_position.y},
                IsMouseButtonDown(MOUSE_BUTTON_LEFT)
        );

        //drag handling
        if     (Clay_PointerOver(temp_elementid = Clay_GetElementId(CLAY_STRING("drag_tiles")))){
            if(!dragging)
                cursor_state = MOUSE_CURSOR_RESIZE_NS;
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                drag_side = drag_side_postive;
                dragging = true;
                dragging_dir = drag_dir_Vf;
                targit_size = &height_tiles_percent;
                temp_elementid = Clay_GetElementId(CLAY_STRING("side_bar"));
                drag_limit = Clay_GetElementData(temp_elementid).boundingBox.height;//bar_width
            }
        }
        else if(Clay_PointerOver(Clay_GetElementId(CLAY_STRING("drag_map_view")))){
            if(!dragging)
                cursor_state = MOUSE_CURSOR_RESIZE_EW;
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                drag_side = drag_side_negtive;
                dragging = true;
                dragging_dir = drag_dir_Hu;
                targit_size = &width_side_bar;
                temp_elementid = Clay_GetElementId(CLAY_STRING("container_lower"));
                drag_limit = Clay_GetElementData(temp_elementid).boundingBox.width - 30;//2*pading + bar_width
            }
        }
        else if(!dragging)
            cursor_state = MOUSE_CURSOR_DEFAULT;

        if(dragging){
            update_drag_size();
        }
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            dragging = false;
        }

        SetMouseCursor(cursor_state);

        //get block point at
        temp_elementdata = Clay_GetElementData(Clay_GetElementId(CLAY_STRING("map_view")));
        if(
            mouse_position.x >= temp_elementdata.boundingBox.x
            && mouse_position.x <= temp_elementdata.boundingBox.x + 8 * 16 * MAP_ZOOM
            &&
            mouse_position.y >= temp_elementdata.boundingBox.y
            && mouse_position.y <= temp_elementdata.boundingBox.y + 8 * 16 * MAP_ZOOM
        ){
            map_view_data.customData.map_view.block_point_at = 
                (int)(mouse_position.x - temp_elementdata.boundingBox.x - map_view_data.customData.map_view.x) / (16 * MAP_ZOOM)
                + (((int)(mouse_position.y - temp_elementdata.boundingBox.y - map_view_data.customData.map_view.y) / (16 * MAP_ZOOM)) * 8);
        }
        else{
            map_view_data.customData.map_view.block_point_at= UINT64_MAX;
        }
        printf("%lu\n",map_view_data.customData.map_view.block_point_at);

        BeginDrawing();
            ClearBackground(BLACK);
            Clay_Raylib_Render(clay_rend_cmd,fonts);
        EndDrawing();
    }

    Clay_Raylib_Close();
    /* CloseWindow(); */
    return 0;
}
