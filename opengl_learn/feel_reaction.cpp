#include "feel_reaction.h"
#include "object_menu_reaction.h"

void del_events()
{


    while (events.size()!=last_event+1)
        events.pop_back();
}

void del_reb(pair<int,int> p1, pair<int,int> p2)
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
}

void add_reb()
{

    vector<Event> vec;

    for (int i=0;i<int(choosen_point.size())-1;i++)
    {
        int x1=choosen_point[i].first;
        int y1=choosen_point[i].second;
        int x2=choosen_point[i+1].first;
        int y2=choosen_point[i+1].second;
        bool ch=0;
        for (int j=0;j<object[x1][y1].reb.size();j++)
            if (object[x1][y1].reb[j].first==x2 && object[x1][y1].reb[j].second==y2)
                ch=1;

        if (ch) continue;
        vec.push_back(Event(mp(x1,y1),mp(x2,y2)));
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

    if (vec.empty()) return;

    del_events();

    events.pb(vec);
    last_event++;

}

void put_element(int i, int j)
{
    if (i==-1) return;
    vector<Event> vec;
    Circle_element fir=object[i][j];
    object[i][j].f.tex=taken;
    object[i][j].f.x1=i*feel_seg_size-feel_seg_size/2.0;
    object[i][j].f.x2=i*feel_seg_size+feel_seg_size/2.0;
    object[i][j].f.y1=j*feel_seg_size-feel_seg_size/2.0;
    object[i][j].f.y2=j*feel_seg_size+feel_seg_size/2.0;
    object[i][j].f.alpha=1.0;
    Circle_element sec=object[i][j];

    vec.pb(Event(fir,sec,{i,j}));

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

    if (vec.empty()) return;

    del_events();

    events.pb(vec);
    last_event++;
}

void add_element()
{


    for (int i=1;i<feel_size;i++)
            for (int j=1;j<feel_size;j++)
            if (object[i][j].f.tex==empty_ && object[i][j].f.alpha==0.5)
            {
                put_element(i,j);
                something_taken=0;
                return;
            }

    put_element(pred_pos.fir,pred_pos.sec);

    pred_pos={-1,-1};
    something_taken=0;


}

void add_point()
{
    vector<Event> vec;
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        if (object[i][j].f.tex==empty_ && object[i][j].f.alpha==0.5)
        {
            Circle_element fir=object[i][j];

            object[i][j].f.tex=connection_point;
            object[i][j].f.alpha=1.0;
            object[i][j].f.resize_(20);

            Circle_element sec=object[i][j];

            vec.pb(Event(fir,sec,{i,j}));
        }
    if (vec.empty()) return;

    del_events();

    events.pb(vec);
    last_event++;

}

void put_point(int i, int j)
{
    taken_point=0;
    if (i==-1) return;
    vector<Event> vec;

    Circle_element f=object[i][j];

    object[i][j].f.tex=connection_point;
    object[i][j].f.resize_(20);
    object[i][j].reb=taken_reb;
    object[i][j].f.alpha=1.0;

    Circle_element s=object[i][j];

    vec.pb(Event(f,s,{i,j}));

    for (auto l:taken_reb)
    {
        vec.pb(Event({i,j},l));
        object[l.fir][l.sec].reb.pb({i,j});
    }

    del_events();

    if (!vec.empty())
        events.pb(vec);
    last_event++;

    taken_point=0;
    taken_reb.clear();
}

void feel_mouse_pressed(int button, int state)
{
    ///------------------------------------DOWN----------------------------------///

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && point_mode_used)
    {
        add_point();
        return;
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && !point_mode_used && !line_mode_used && !move_mode_used)
    {
        for (int i=1;i<feel_size;i++)
            for (int j=1;j<feel_size;j++)
            {
                if (object[i][j].f.in_dinamic() && object[i][j].f.tex!=empty_ && object[i][j].f.tex!=connection_point && object[i][j].f.tex!=choosen_point_tex)
                {
                    object[i][j].shade=0.16;

                    float x1=(object[i][j].f.x1-startx)*scrol;
                    float x2=(object[i][j].f.x2-startx)*scrol;
                    float y1=(object[i][j].f.y1-starty)*scrol;
                    float y2=(object[i][j].f.y2-starty)*scrol;
                    float x=(x1+x2)/2.0;
                    float y=(y1+y2)/2.0;

                    x=min(x,WinWid-300);
                    y=min(y,WinHei-75);

                    object_info=Figure(x,x+150,y,y+75,left_menu_background_tex,1.0);

                    object_delete=Button_do(Figure(x+150,x+225,y,y+75,left_menu_vertical[0].tex,1.0),&object_delete_func);
                    object_rotate=Button_do(Figure(x+225,x+300,y,y+75,left_menu_vertical[0].tex,1.0),&object_rotate_func);


                    choosen_object={i,j};
                }
            }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && move_mode_used)
    {
        for (int i=1;i<feel_size;i++)
            for (int j=1;j<feel_size;j++)
            {
                if (object[i][j].f.in_dinamic() && object[i][j].f.tex!=empty_ && object[i][j].f.tex!=connection_point && object[i][j].f.tex!=choosen_point_tex)
                {
                    GLuint tex=object[i][j].f.tex;
                    pred_pos={i,j};
                    direction=get_dir(tex);
                    choosen_object={i,j};
                    object_delete_func();
                    choosen_object={-1,-1};
                    taken=tex;
                    something_taken=1;
                }
                if (object[i][j].f.in_circle() && object[i][j].f.tex==connection_point)
                {
                    bool ch=0;
                    for (auto l:object[i][j].reb)
                        if (object[l.fir][l.sec].f.tex!=empty_ && object[l.fir][l.sec].f.tex!=connection_point)
                        ch=1;
                    if (ch) continue;
                    pred_pos={i,j};
                    taken_point=1;
                    taken_reb=object[i][j].reb;
                    vector<Event> vec;

                    Circle_element f=object[i][j];

                    object[i][j].f.tex=empty_;
                    object[i][j].f.resize_(40);
                    Circle_element s=object[i][j];
                    vec.pb(Event(f,s,{i,j}));

                    for (auto l:taken_reb)
                    {
                        del_reb(l,{i,j});
                        vec.pb(Event(l,{i,j},3));
                    }


                    del_events();

                    if (!vec.empty())
                        events.pb(vec);
                    last_event++;

                }
            }
    }

    ///------------------------------------UP----------------------------------///

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && line_mode_used && pressed==NULL)
    {
        add_reb();
        return;
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && something_taken)
    {
        add_element();
        return;
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP && taken_point)
    {
        float mn=10000;
        pair<int,int> imn={-1,-1};
        for (int i=1;i<feel_size;i++)
            for (int j=1;j<feel_size;j++)
                if (abs(object[i][j].f.alpha-0.5)<0.00001)
                {
                    imn={i,j};
                }

        int i=imn.fir;
        int j=imn.sec;

        if (i==-1)
        {
            i=pred_pos.fir;
            j=pred_pos.sec;
        }

        put_point(i,j);
        pred_pos={-1,-1};
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (pressed!=NULL)
        {
            if ((*pressed).used) (*pressed).shade=0.16; else
                (*pressed).shade=0.0;
            pressed=NULL;
        }

        if (pressed_do!=NULL)
        {
            (*pressed_do).press_up();
            pressed_do=NULL;
        }

        if (choosen_object!=make_pair(-1,-1))
        {
            object[choosen_object.fir][choosen_object.sec].shade=0.0;
            if (object[choosen_object.fir][choosen_object.sec].f.in_dinamic())
            {
                object_menu_used=1;
            } else
            {
                choosen_object={-1,-1};
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
            if (something_taken)
            {
                put_element(pred_pos.fir,pred_pos.sec);
                pred_pos={-1,-1};
                something_taken=0;
            }
            if (taken_point)
            {
                put_point(pred_pos.fir,pred_pos.sec);
                pred_pos={-1,-1};
            }
        }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (line_mode.f.in() && !point_mode_used && !move_mode_used)
        {
            line_mode.press_down();
            pressed=&line_mode;
        }
        if (point_mode.f.in() && !line_mode_used && !move_mode_used)
        {
            point_mode.press_down();
            pressed=&point_mode;
        }
        if (move_mode.f.in() && !line_mode_used && !point_mode_used)
        {
            move_mode.press_down();
            pressed=&move_mode;
        }

        if (delete_mode.f.in() && !line_mode_used && !point_mode_used && !move_mode_used)
        {
            delete_mode.press_down();
            pressed=&delete_mode;
        }

        if (undo_button.f.in() && !line_mode_used && !point_mode_used && !move_mode_used)
        {
            undo_button.press_down();
            cout<<'!'<<'\n';
            pressed_do=&undo_button;
        }

        if (redo_button.f.in() && !line_mode_used && !point_mode_used && !move_mode_used)
        {
            redo_button.press_down();
            pressed_do=&redo_button;
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

        if (pressed_do!=NULL)
        {
            (*pressed_do).press_up();
            pressed_do=NULL;
        }

        if (choosen_object!=make_pair(-1,-1))
        {
            object[choosen_object.fir][choosen_object.sec].shade=0.0;
            choosen_object={-1,-1};
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
