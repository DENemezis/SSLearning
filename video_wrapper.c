#include "video_wrapper.h" 

void video_init() {
    vdp_sync_vblank_out_set(vblank_in_handler, NULL);

    vdp2_scrn_back_color_set(VDP2_VRAM_ADDR(3, 0x01FFFE), RGB1555(1, 0, 3, 15)); 
    vdp2_tvmd_display_set(); 
}

static void cmdt_list_init(void) {
    static const int16_vec2_t system_clip_coord = INT16_VEC2_INITIALIZER(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    cmdt_list = vdp1_cmdt_list_alloc(ORDER_COUNT);
    (void)memset(&cmdt_list->cmdts[0], 0x00, sizeof(vdp1_cmdt_t) * ORDER_COUNT);

    cmdt_list->count = ORDER_COUNT;

    vdp1_cmdt_t *cmdts;
    cmdts = &cmdt_list->cmdts[0];

    vdp1_cmdt_system_clip_coord_set(&cmdts[ORDER_SYSTEM_CLIP_COORDS_INDEX]);
    vdp1_cmdt_vtx_system_clip_coord_set(&cmdts[ORDER_SYSTEM_CLIP_COORDS_INDEX], system_clip_coord);

    vdp1_cmdt_end_set(&cmdts[ORDER_DRAW_END_INDEX]);
}

static void vblank_in_handler(void *work __unused) { 
    smpc_peripheral_intback_issue(); 
} 

static void vblank_out_handler(void *param) {
    smpc_peripheral_intback_issue();
}



void draw(quad* q) { 
    static const int16_vec2_t local_coord_center =
            INT16_VEC2_INITIALIZER((SCREEN_WIDTH / 2) - SIZE - 1, (SCREEN_HEIGHT / 2) - SIZE - 1);

    vdp1_cmdt_t *cmdt_local_coords;
    cmdt_local_coords = &cmdt_list->cmdts[ORDER_LOCAL_COORDS_INDEX];

    vdp1_cmdt_local_coord_set(cmdt_local_coords);
    vdp1_cmdt_vtx_local_coord_set(cmdt_local_coords, local_coord_center);

    vdp1_cmdt_t *cmdt_polygon;
    cmdt_polygon = &cmdt_list->cmdts[ORDER_POLYGON_INDEX];

    vdp1_cmdt_polyline_set(cmdt_polygon);
    vdp1_cmdt_color_set(cmdt_polygon, q.color);
    vdp1_cmdt_draw_mode_set(cmdt_polygon, primitive_draw_modes[q.draw_mode]);
    vdp1_cmdt_vtx_set(cmdt_polygon, &q.points[0]);
}