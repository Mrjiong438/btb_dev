#define CLAY_IMPLEMENTATION
#include"clay.h"
#include<stdio.h>
#include<stdint.h>
#include"raylib.h"
#include"renderers/clay_renderer_raylib.c"

#define COLOR_DARK  {109,128,181,255}
#define COLOR_LIGHT {248,248,255,255}
#define COLOR_BACK  {47,79,79,255}

void HandleClayErrors(Clay_ErrorData errorData) {
    // See the Clay_ErrorData struct for more information
    printf("%s", errorData.errorText.chars);
}

uint16_t monitor_n;
uint16_t monitor_w;
uint16_t monitor_h;
uint16_t sczoom = 1;
btb_data_t current_map;

int main(){
    btb_mapread(&current_map,"./the4.btb");
    CustomLayoutElement cus = {
        .type = CUSTOM_LAYOUT_ELEMENT_TYPE_MAP_VIEW,
        .customData.map_view = (CustomLayoutElement_map_view){
            .map_data = current_map,
            .x = 0,
            .y = 0,
            .zoom = 1
        }
    };

    uint64_t clay_min_mem = Clay_MinMemorySize();
    Clay_Arena clay_mem = (Clay_Arena){
        .memory = malloc(clay_min_mem),
        .capacity = clay_min_mem
    };
    SetTargetFPS(120);
    Clay_Raylib_Initialize(1600,1200,"btb_editor",FLAG_WINDOW_RESIZABLE);
    /* Clay_Raylib_Initialize(2560,1440,"btb_editor",FLAG_WINDOW_RESIZABLE); */
    /* MaximizeWindow(); */
    Clay_Initialize(
            clay_mem,(Clay_Dimensions){
                .width = GetScreenWidth(),
                .height = GetScreenHeight()
            },
            (Clay_ErrorHandler) { HandleClayErrors, 0}
    );
    /* InitWindow(1600,1200,"btb_editor"); */
    /* monitor_n = GetCurrentMonitor(); */
    /* monitor_w = GetMonitorWidth(monitor_n); */
    /* monitor_h = GetMonitorHeight(monitor_n); */
    /* if((monitor_w / 2) > (monitor_h / 2)) */
    /*     sczoom = (monitor_w / 2); */
    /* else */
    /*     sczoom = (monitor_h / 2); */
    /* SetWindowSize(sczoom,sczoom); */
    /* SetWindowPosition((monitor_w - GetScreenWidth()) / 2,(monitor_h - GetScreenHeight()) / 2); */
    /* ToggleFullscreen(); */
    /* ToggleBorderlessWindowed(); */
    Font fonts[2];
    fonts[0] = LoadFontEx("resources/Roboto-Regular.ttf", 48, 0, 400);
    SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);

    Vector2 mouse_position;
    Vector2 whell_delta;
    MouseCursor cursor_state;

    while(!WindowShouldClose()){
        mouse_position = GetMousePosition();
        /* whell_delta = GetMouseWheelMoveV(); */
        Clay_SetPointerState(
                (Clay_Vector2){mouse_position.x,mouse_position.y},
                IsMouseButtonDown(0)
        );
        cursor_state = MOUSE_CURSOR_DEFAULT;
        /* SetMouseCursor(MOUSE_CURSOR_DEFAULT); */

        Clay_SetLayoutDimensions((Clay_Dimensions){
                .width = GetScreenWidth(),
                .height = GetScreenHeight()
        });
        Clay_BeginLayout();
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
                            .custom = {.customData = &cus},
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
                        if(Clay_Hovered())
                            cursor_state = MOUSE_CURSOR_RESIZE_EW;
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
                                .width = CLAY_SIZING_FIXED(250),
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
                                    .height = CLAY_SIZING_GROW(0)
                                }
                            }
                        }){}
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
                            if(Clay_Hovered())
                                cursor_state = MOUSE_CURSOR_RESIZE_NS;
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

        SetMouseCursor(cursor_state);
            Clay_RenderCommandArray clay_rend_cmd = Clay_EndLayout();

        BeginDrawing();
            ClearBackground(BLACK);
            Clay_Raylib_Render(clay_rend_cmd,fonts);
        EndDrawing();
    }

    Clay_Raylib_Close();
    /* CloseWindow(); */
    return 0;
}
