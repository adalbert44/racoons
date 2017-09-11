#include "delete_mode_reaction.h"

/*void del_reb(pair<int,int> p1, pair<int,int> p2)
{
    vector<pair<int,int> > new_;
    for (auto i: object[p1.fir][p1.sec].reb)
        if (i!=p2) new_.pb(i);
    object[p1.fir][p1.sec].reb=new_;

    new_.clear();

    for (auto i: object[p2.fir][p2.sec].reb)
        if (i!=p1) new_.pb(i);
    object[p2.fir][p2.sec].reb=new_;

    new_.clear();
}*/

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
}
