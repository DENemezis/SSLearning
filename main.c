#include <yaul.h>

#include <stdio.h>
#include <stdlib.h>

#include "video_wrapper.h"

smpc_peripheral_digital_t digital;

static void _vblank_in_handler(void *work __unused) { smpc_peripheral_intback_issue(); } 

void user_init(void)
{
  smpc_peripheral_init();
 
  vdp_sync_vblank_out_set(_vblank_in_handler, NULL);

  vdp2_scrn_back_color_set(VDP2_VRAM_ADDR(3, 0x01FFFE),
  RGB1555(1, 0, 3, 15)); 
  
  vdp1_env_t env;
  vdp1_env_default_init(&env);

  env.erase_color = RGB1555(1, 0, 3, 15);

  vdp1_env_set(&env);

  vdp_sync_vblank_out_set(vblank_out_handler, NULL);

  vdp2_tvmd_display_set(); 
  
  vdp1_vram_partitions_get(&vdp1_vram_partitions);

  vdp2_sync();
  vdp2_sync_wait();
}

void init(){
  dbgio_init();
  dbgio_dev_default_init(DBGIO_DEV_VDP2);
  dbgio_dev_font_load(); 
  
  vdp_sync_vblank_in_set(_vblank_in_handler, NULL); 

  video_init(); 
}
 
void control() {
    smpc_peripheral_process();
    smpc_peripheral_digital_port(1, &digital);

    const uint16_t pressed_state = digital.pressed.raw;

    if ((pressed_state & PERIPHERAL_DIGITAL_A) != 0) {
        dbgio_printf("Button A was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_B) != 0) {
        dbgio_printf("Button B was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_C) != 0) {
        dbgio_printf("Button C was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_X) != 0) {
        dbgio_printf("Button X was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_Y) != 0) {
        dbgio_printf("Button Y was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_Z) != 0) {
        dbgio_printf("Button Z was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_UP) != 0) {
        dbgio_printf("Button UP was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_DOWN) != 0) {
        dbgio_printf("Button DOWN was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_LEFT) != 0) {
        dbgio_printf("Button LEFT was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_RIGHT) != 0) {
        dbgio_printf("Button RIGHT was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_R) != 0) {
        dbgio_printf("Button R shoulder was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_L) != 0) {
        dbgio_printf("Button L shoulder was pressed!\n\r");
    }
    if ((pressed_state & PERIPHERAL_DIGITAL_START) != 0) {
        dbgio_printf("Button START was pressed!\n\r");
    }
}

static void vblank_out_handler(void *work __unused)
{
    smpc_peripheral_intback_issue();
}

 
quad q;
 
int main(void)
{
  init();
  q.type = TYPE_POLYGON;
  q.draw_mode = DRAW_MODE_NORMAL;
  q.color = RGB1555(1, 31, 0, 31);  

  q.points[0].x = 0;
  q.points[0].y = 31;

  q.points[1].x = 31;
  q.points[1].y = 31;

  q.points[2].x = 31;
  q.points[2].y = 0;

  q.points[3].x = 0;
  q.points[3].y = 0;

  while(true){

    dbgio_printf("\x1b[H\x1b[2J");  // clears the screen
    dbgio_printf("Press a key to test your controller! \n\r\n\r");  // clears the screen
    control(); 
 
    draw(&q);
    
    dbgio_flush(); 
    
    vdp1_sync_render();
    vdp1_sync();
    vdp2_sync();
    vdp2_sync_wait();
  }

  return 0;
}

