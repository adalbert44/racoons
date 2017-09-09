#include "object_menu_reaction.h"
#include "feel_reaction.h"

void try_del(int i, int j, pair<int,int> p, vector<Event> &vec)
{
    vector<pair<int,int> > new_;

    for (auto l:object[i][j].reb)
        if (l!=p)
        new_.pb(l);

    if (new_.empty())
    {
        Circle_element fir=object[i][j];
        object[i][j].reb.clear();
        object[i][j].f.tex=empty_;
        object[i][j].f.resize_(40);
        Circle_element sec=object[i][j];
        vec.pb(Event(fir,sec,{i,j}));
    } else
    {
        object[i][j].reb=new_;
    }
}

int object_delete_func()
{
    vector<Event> vec;

    int i=choosen_object.fir;
    int j=choosen_object.sec;

    Circle_element fir=object[i][j];

    object[i][j].f.tex=empty_;
    for (int l=0;l<object[i][j].reb.size();l++)
    {
        try_del(object[i][j].reb[l].fir,object[i][j].reb[l].sec,{i,j},vec);
        vec.pb(Event({i,j},object[i][j].reb[l],3));
    }



    object[i][j].reb.clear();
    object[i][j].f.resize_(40);

    Circle_element sec=object[i][j];

    vec.pb(Event(fir,sec,{i,j}));

    del_events();
    events.pb(vec);
    last_event++;
    choosen_object={-1,-1};
    object_menu_used=0;
}

GLuint get_next(GLuint tex)
{
    for (int i=0;i<7;i++)
        if (tex==left_menu_horizontal[i].tex) return(left_menu_vertical[i].tex);

    for (int i=0;i<7;i++)
        if (tex==left_menu_vertical[i].tex) return(left_menu_horizontal[i].tex);
}

bool get_dir(GLuint tex)
{
    for (int i=0;i<7;i++)
        if (tex==left_menu_horizontal[i].tex) return(1);

    for (int i=0;i<7;i++)
        if (tex==left_menu_vertical[i].tex) return(0);
}

int object_rotate_func()
{
    vector<Event> vec;

    int i=choosen_object.fir;
    int j=choosen_object.sec;

    GLuint tex=object[i][j].f.tex;

    Circle_element f=object[i][j];

    object[i][j].f.tex=empty_;
    Circle_element fir=object[i][j];
    for (int l=0;l<object[i][j].reb.size();l++)
    {
        try_del(object[i][j].reb[l].fir,object[i][j].reb[l].sec,{i,j},vec);
        vec.pb(Event({i,j},object[i][j].reb[l],3));
    }


    object[i][j].reb.clear();

    Circle_element sec=object[i][j];

    choosen_object={-1,-1};
    object_menu_used=0;

    ///delete

    tex=get_next(tex);
    object[i][j].f.tex=tex;

    bool direction=get_dir(tex);

    if (direction)
                {

                    if (i+1<feel_size)
                    {

                        vec.pb(Event(mp(i+1,j),mp(i,j)));
                        object[i][j].reb.push_back({i+1,j});
                        object[i+1][j].reb.push_back({i,j});

                        if (object[i+1][j].f.tex!=connection_point)
                        {
                            Circle_element fir=object[i+1][j];

                            object[i+1][j].f.tex=connection_point;
                            object[i+1][j].f.alpha=1.0;
                            object[i+1][j].f.resize_(20);

                            Circle_element sec=object[i+1][j];
                            vec.pb(Event(fir,sec,{i+1,j}));
                        }


                    }

                    if (i-1>=1)
                    {
                        vec.pb(Event(mp(i-1,j),mp(i,j)));
                        object[i][j].reb.push_back({i-1,j});
                        object[i-1][j].reb.push_back({i,j});

                        if (object[i-1][j].f.tex!=connection_point)
                        {
                            Circle_element fir=object[i-1][j];

                            object[i-1][j].f.tex=connection_point;
                            object[i-1][j].f.alpha=1.0;
                            object[i-1][j].f.resize_(20);

                            Circle_element sec=object[i-1][j];
                            vec.pb(Event(fir,sec,{i-1,j}));
                        }


                    }

                } else
                {

                    if (j+1<feel_size)
                    {
                        vec.pb(Event(mp(i,j+1),mp(i,j)));
                        object[i][j].reb.push_back({i,j+1});
                        object[i][j+1].reb.push_back({i,j});

                        if (object[i][j+1].f.tex!=connection_point)
                        {
                            Circle_element fir=object[i][j+1];

                            object[i][j+1].f.tex=connection_point;
                            object[i][j+1].f.alpha=1.0;
                            object[i][j+1].f.resize_(20);

                            Circle_element sec=object[i][j+1];
                            vec.pb(Event(fir,sec,{i,j+1}));
                        }
                    }
                    if (j-1>=1)
                    {

                        vec.pb(Event(mp(i,j-1),mp(i,j)));
                        object[i][j].reb.push_back({i,j-1});
                        object[i][j-1].reb.push_back({i,j});

                        if (object[i][j-1].f.tex!=connection_point)
                        {
                            Circle_element fir=object[i][j-1];

                            object[i][j-1].f.tex=connection_point;
                            object[i][j-1].f.alpha=1.0;
                            object[i][j-1].f.resize_(20);

                            Circle_element sec=object[i][j-1];
                            vec.pb(Event(fir,sec,{i,j-1}));
                        }
                    }
                }
        Circle_element s=object[i][j];
        vec.pb(Event(f,s,{i,j}));
    del_events();
    events.pb(vec);
    last_event++;

}

void object_menu_mouse_pressed(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {

        if (object_delete.f.in())
        {
            object_delete.press_down();
            pressed_do=&object_delete;
        } else
        if (object_rotate.f.in())
        {
            object_rotate.press_down();
            pressed_do=&object_rotate;
        } else
        if (!object_info.in())
        {
            choosen_object={-1,-1};
            object_menu_used=0;
        }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (pressed_do!=NULL)
        {
            if ((*pressed_do).f.in())
            {
                (*pressed_do).shade=0.0;
                (*pressed_do).to_do();
            }
        }
        pressed_do=NULL;
    }

}
