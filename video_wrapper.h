#ifndef VIDEO_WRAPPER_H
#define VIDEO_WRAPPER_H

#include <yaul.h>

#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 224 

#define TYPE_POLYLINE (0)
#define TYPE_POLYGON  (1)
#define TYPE_COUNT    (2) 

#define DRAW_MODE_NORMAL                (0)
#define DRAW_MODE_MESH                  (1)
#define DRAW_MODE_SHADOW                (2)
#define DRAW_MODE_HALF_LUMINANCE        (3)
#define DRAW_MODE_HALF_TRANSPARENT      (4)
#define DRAW_MODE_GOURAUD_SHADING       (5)
#define DRAW_MODE_GOURAUD_HALF_LUM      (6)
#define DRAW_MODE_GOURAUD_HALF_TRANS    (7)
#define DRAW_MODE_COUNT                 (8)
 
#define ORDER_SYSTEM_CLIP_COORDS_INDEX  0
#define ORDER_LOCAL_COORDS_INDEX        1
#define ORDER_POLYGON_INDEX             2
#define ORDER_DRAW_END_INDEX            3
#define ORDER_COUNT                     4

#define CMDT_VTX_POLYGON_A 0
#define CMDT_VTX_POLYGON_B 1 
#define CMDT_VTX_POLYGON_C 2
#define CMDT_VTX_POLYGON_D 3

void video_init();

static void cmdt_list_init(void);
static vdp1_cmdt_list_t *cmdt_list = NULL;
static vdp1_vram_partitions_t vdp1_vram_partitions;

static void vblank_in_handler(void *work __unused);
static void vblank_out_handler(void *);

static vdp1_cmdt_draw_mode_t primitive_draw_modes[] = {
        {
                .raw = 0x0000
        },
        {
                .mesh_enable = true
        },
        {
                .cc_mode = 1
        },
        {
                .cc_mode = 2
        },
        {
                .cc_mode = 3
        },
        {
                .cc_mode = 4
        },
        {
                .cc_mode = 6
        },
        {
                .cc_mode = 7
        }
};

typedef struct {
        int8_t type;
        int8_t draw_mode;
        rgb1555_t color;
        int16_vec2_t points[4];
} quad;

void draw(quad* q);

#endif // VIDEO_WRAPPER_H