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

    if (rezistor(object[i][j].f.tex))
    {
        string to_draw="R=";
        to_draw+=parse_to_string(object[i][j].R);
        drawstring(object_info.x1+20,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
    }

    if (ampermetr(object[i][j].f.tex))
    {
        ld I=0;
        for (auto to: object[i][j].reb)
        {
            I+=max(power[i][j][to.fir][to.sec],ld(0));
            I=min(I,ld(inf));
        }


        string to_draw="I=";

        if (I<inf)
            to_draw+=parse_to_string(I); else
            to_draw+="inf";
        drawstring(object_info.x1+20,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
    }

    if (voltmetr(object[i][j].f.tex))
    {
        ld U=0;
        pair<int,int> to=object[i][j].reb[0];
        U+=potential[to.fir][to.sec];

        to=object[i][j].reb[1];
        U-=potential[to.fir][to.sec];
        string to_draw="U=";

        if (potential[to.fir][to.sec]!=inf)
            to_draw+=parse_to_string(U); else
            to_draw+="inf";
        drawstring(object_info.x1+20,(object_info.y2+object_info.y1)/2.0+10,1.0,to_draw);
    }


}


