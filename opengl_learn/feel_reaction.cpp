#include "feel_reaction.h"

void feel_mouse_pressed(int button, int state)
{
    if (something_taken && state==GLUT_UP && button==GLUT_LEFT_BUTTON)
    {
        for (int i=1;i<feel_size;i++)
            for (int j=1;j<feel_size;j++)
            if (object[i][j].f.tex==empty_ && object[i][j].f.alpha==0.5)
            {
                object[i][j].f.tex=taken;
                object[i][j].f.x1=i*feel_seg_size-feel_seg_size/2.0;
                object[i][j].f.x2=i*feel_seg_size+feel_seg_size/2.0;
                object[i][j].f.y1=j*feel_seg_size-feel_seg_size/2.0;
                object[i][j].f.y2=j*feel_seg_size+feel_seg_size/2.0;
                object[i][j].f.alpha=1.0;

                if (direction)
                {
                    if (i+1<feel_size)
                    {
                        object[i][j].reb.push_back({i+1,j});
                        object[i+1][j].reb.push_back({i,j});
                        object[i+1][j].f.tex=connection_point;
                        object[i+1][j].f.alpha=1.0;
                        object[i+1][j].f.resize_(20);
                    }

                    if (i-1>=1)
                    {
                        object[i][j].reb.push_back({i-1,j});
                        object[i-1][j].reb.push_back({i,j});
                        object[i-1][j].f.tex=connection_point;
                        object[i-1][j].f.alpha=1.0;
                        object[i-1][j].f.resize_(20);
                    }

                } else
                {
                    if (j+1<feel_size)
                    {
                        object[i][j].reb.push_back({i,j+1});
                        object[i][j+1].reb.push_back({i,j});
                        object[i][j+1].f.tex=connection_point;
                        object[i][j+1].f.alpha=1.0;
                        object[i][j+1].f.resize_(20);
                    }

                    if (j-1>=1)
                    {
                        object[i][j].reb.push_back({i,j-1});
                        object[i][j-1].reb.push_back({i,j});
                        object[i][j-1].f.tex=connection_point;
                        object[i][j-1].f.alpha=1.0;
                        object[i][j-1].f.resize_(20);
                    }
                }
            }

        something_taken=0;
    }
}

void left_menu_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        for (int i=0;i<7;i++)
            if (left_menu_horizontal[i].in())
            {
                something_taken=1;
                taken=left_menu_horizontal[i].tex;
                direction=1;
            }
        for (int i=0;i<7;i++)
            if (left_menu_vertical[i].in())
            {
                something_taken=1;
                taken=left_menu_vertical[i].tex;
                direction=0;
            }
    } else
    if (state==GLUT_UP)
    {
        something_taken=0;
    }
}
