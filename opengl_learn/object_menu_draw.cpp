#include "object_menu_draw.h"

void object_menu_draw()
{
    int i=choosen_object.fir;
    int j=choosen_object.sec;
    window_shade.alpha=0.1;
    window_shade.draw_state();

    object_info.draw_state();

    if (!(object[i][j].f.tex==choosen_point_tex || object[i][j].f.tex==connection_point && !can_delete(i,j)))
        object_delete.draw_state();

    if (object[i][j].f.tex!=choosen_point_tex && object[i][j].f.tex!=connection_point)
        object_rotate.draw_state();
}


