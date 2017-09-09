#include "object_menu_draw.h"

void object_menu_draw()
{
    window_shade.alpha=0.1;
    window_shade.draw_state();

    object_info.draw_state();
    object_delete.draw_state();
    object_rotate.draw_state();
}
