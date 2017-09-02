#include "feel_reaction.h"

void add_reb()
{

    for (int i=0;i<int(choosen_point.size())-1;i++)
    {
        int x1=choosen_point[i].first;
        int y1=choosen_point[i].second;
        int x2=choosen_point[i+1].first;
        int y2=choosen_point[i+1].second;
        bool ch=0;
        for (int j=0;j<object[x1][y1].reb.size();j++)
            if (object[x1][y1].reb[j].first==x2 && object[x1][y1].reb[j].first==y2)
                ch=1;
        if (ch) continue;
        object[x1][y1].reb.push_back({x2,y2});
        object[x2][y2].reb.push_back({x1,y1});
    }



    for (int i=0;i<choosen_point.size();i++)
    {
        int x1=choosen_point[i].first;
        int y1=choosen_point[i].second;
        object[x1][y1].f.tex=connection_point;
    }

    choosen_point.clear();
}

void add_element()
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

void add_point()
{
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        if (object[i][j].f.tex==empty_ && object[i][j].f.alpha==0.5)
        {
            object[i][j].f.tex=connection_point;
            object[i][j].f.alpha=1.0;
            object[i][j].f.resize_(20);
        }

}

void feel_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && line_mode_used && pressed==NULL)
    {
        add_reb();
        return;
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && point_mode_used)
    {
        add_point();
        return;
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && something_taken)
    {
        add_element();
        return;
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (pressed!=NULL)
        {
            if ((*pressed).f.in())
            {
                (*pressed).press_up();
            } else
            {

                if ((*pressed).used) (*pressed).shade=0.16; else
                    (*pressed).shade=0.0;
                pressed=NULL;
            }
        }
    }
}

void left_menu_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && line_mode_used && pressed==NULL)
    {
        add_reb();
        return;
    }

    if (!line_mode_used && !point_mode_used)
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
        if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
        {
            something_taken=0;
        }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (line_mode.f.in() && !point_mode_used)
        {
            line_mode.press_down();
            pressed=&line_mode;
        }
        if (point_mode.f.in() && !line_mode_used)
        {
            point_mode.press_down();
            pressed=&point_mode;
        }

    } else
    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (pressed!=NULL)
        {
            if ((*pressed).f.in())
            {
                (*pressed).press_up();
                pressed=NULL;
            } else
            {

                if ((*pressed).used) (*pressed).shade=0.16; else
                    (*pressed).shade=0.0;
                pressed=NULL;
            }
        }
    }
}

void add_point_to_choosen()
{
    if (pressed!=NULL) return;
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        if (object[i][j].f.tex==connection_point && object[i][j].f.in_circle())
        {
            object[i][j].f.tex=choosen_point_tex;
            choosen_point.push_back({i,j});
        }
}
