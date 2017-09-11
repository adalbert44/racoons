#include "delete_mode_reaction.h"


void delete_mode_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (delete_mode.f.in())
        {
            delete_mode.press_down();
            pressed=&delete_mode;
        }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && pressed!=NULL)
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

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        vector<Event> vec;
        for (auto l:to_del_point)
        {
            int i=l.fir;
            int j=l.sec;


            object[i][j].f.tex=connection_point;
            Circle_element fir=object[i][j];
            object[i][j].f.tex=empty_;
            object[i][j].f.resize_(40);

            vector<pair<int,int> > r=object[i][j].reb;

            for(auto l:r)
            {
                del_reb(l,{i,j});
                vec.pb(Event(l,{i,j},3));
            }

            Circle_element sec=object[i][j];

            vec.pb(Event(fir,sec,{i,j}));


        }

        if (!vec.empty())
        {
            del_events();
            events.pb(vec);
            last_event++;
        }

        to_del_point.clear();
    }
}

bool intersect(pair<float, float> p1, pair <float, float> p2, pair<float,float> p3, pair<float,float> p4)
{

}

bool can_delete(int i, int j)
{
    if (object[i][j].f.tex!=connection_point) return(0);
    for (auto l:object[i][j].reb)
    {
        if (object[l.fir][l.sec].f.tex!=connection_point && object[l.fir][l.sec].f.tex!=choosen_point_tex) return(0);
    }
    return(1);
}

void delete_mode_mouse_pressed_motion(float x1, float y1, float x2, float y2)
{
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            if (can_delete(i,j) && object[i][j].f.in_circle())
            {
                object[i][j].f.tex=choosen_point_tex;
                to_del_point.pb({i,j});
            }

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            for (auto l:object[i][j].reb)
            {
                float xx1=((object[i][j].f.x1-startx)*scrol+(object[i][j].f.x2-startx)*scrol)/2.0;
                float yy1=((object[i][j].f.y1-starty)*scrol+(object[i][j].f.y2-starty)*scrol)/2.0;
                float xx2=((object[l.fir][l.sec].f.x1-startx)*scrol+(object[l.fir][l.sec].f.x2-startx)*scrol)/2.0;
                float yy2=((object[l.fir][l.sec].f.y1-starty)*scrol+(object[l.fir][l.sec].f.y2-starty)*scrol)/2.0;

                if (intersect({xx1,yy1},{xx2,yy2},{x1,y1},{x2,y2}))
                    {
                        choosen_reb[i][j][l.fir][l.sec]=1;
                        choosen_reb[l.fir][l.sec][i][j]=1;
                    }
            }
}
