#include "feel_draw.h"
#include "basik_classes.h"

bool can_put(int i, int j)
{
    if ((object[i][j].f.x2-startx)*scrol<=left_menu_size) return(0);
    if (object[i][j].f.tex!=empty_) return(0);
    if (i-1!=0)
        if (object[i-1][j].f.tex!=empty_ && object[i-1][j].f.tex!=connection_point) return(0);
    if (i+1!=feel_size)
        if (object[i+1][j].f.tex!=empty_ && object[i+1][j].f.tex!=connection_point) return(0);
    if (j-1!=0)
        if (object[i][j-1].f.tex!=empty_ && object[i][j-1].f.tex!=connection_point) return(0);
    if (j+1!=feel_size)
        if (object[i][j+1].f.tex!=empty_ && object[i][j+1].f.tex!=connection_point) return(0);
    return(1);
}


void draw_feel()
{




    for (int i=0;i<int(feel_background.size());i++)
        feel_background[i].draw();

    float mn=100000;
    int imn=0;
    int jmn=0;

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            if (object[i][j].f.tex==empty_)
                object[i][j].f.alpha=0.12;
            if (object[i][j].f.centre_dist()<mn)
            {
                imn=i;
                jmn=j;
                mn=object[i][j].f.dist();

            }
        }
    if (can_put(imn,jmn) && mousex>left_menu_size)
        object[imn][jmn].f.alpha=0.5;

    for (int i=1;i<feel_size;i++)

        for (int j=1;j<feel_size;j++)
        {
            if ((object[i][j].f.tex==empty_ && (!can_put(i,j) || !(something_taken || point_mode_used || taken_point))) || object[i][j].f.tex==connection_point || object[i][j].f.tex==choosen_point_tex)
                continue;
            object[i][j].draw();

        }

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            if (object[i][j].f.tex==connection_point || object[i][j].f.tex==choosen_point_tex)
            {
                object[i][j].draw();
            }
        }


    if (something_taken)
    {
        Figure now=Figure(mousex-feel_seg_size*scrol/2.0,mousex+feel_seg_size*scrol/2.0,
                          mousey-feel_seg_size*scrol/2.0,mousey+feel_seg_size*scrol/2.0,taken,0.2);
        now.draw_state();
    }

    if (taken_point)
    {
            Figure now=Figure(mousex-10*scrol,mousex+10*scrol,
                          mousey-10*scrol,mousey+10*scrol,connection_point,0.2);
        now.draw_state();

    }
}

void draw_left_menu()
{
    //cout<<left_menu_background.y1<<' '<<left_menu_background.y2<<'\n';
    left_menu_background.draw_state();
    for (int i=0;i<7;i++)
    {
        left_menu_horizontal[i].draw_state();
        left_menu_vertical[i].draw_state();
        //cout<<left_menu_vertical[i].tex<<'\n';
    }
    point_mode.draw_state();
    line_mode.draw_state();
    move_mode.draw_state();
    undo_button.draw_state();
    redo_button.draw_state();
}
