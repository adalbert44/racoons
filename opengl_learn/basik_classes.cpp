#include "basik_classes.h"


float WinWid=0.0;
float WinHei=0.0;

float speed_scrol=1.05;
float speed_move=20.0;



Figure window_shade;
Figure object_info;
Button_do object_delete;
Button_do object_rotate;
pair<int,int> pred_pos={-1,-1};

float feel_seg_size=100;
int feel_size=30;
float scrol=1.0;
float mousex=0.0, mousey=0.0;
bool in_feel=1;
bool something_taken=0;
bool direction=0;
GLuint taken;
GLuint put;
float left_menu_size=350;
float startx=-left_menu_size,starty=0;
GLuint feel_background_texture[2];
GLuint empty_;
GLuint connection_point;
vector<Figure> feel_background;
Figure left_menu_background;
Circle_element object[30][30];
GLuint left_menu_background_tex;
GLuint line_mode_tex;
GLuint point_mode_tex;
Button_do *pressed_do=NULL;
bool taken_point=0;
vector<pair<int,int> > taken_reb;

Figure left_menu_vertical[9];
Figure left_menu_horizontal[9];

vector<pair<int,int> > choosen_point;
GLuint choosen_point_tex;
vector<vector<Event> > events;
int last_event=-1;

Button line_mode;
Button move_mode;
Button point_mode;
bool line_mode_used=0;
bool point_mode_used=0;
bool move_mode_used=0;
Button_do undo_button;
Button_do redo_button;
Button* pressed=NULL;
pair<int,int> choosen_object={-1,-1};
bool object_menu_used=0;

float sqr(float a)
{
    return(a*a);
}

float dist_(float x1, float y1, float x2, float y2)
{
    return(sqrt(sqr(x1-x2)+sqr(y1-y2)));
}

Figure :: Figure()
{

}

Figure :: Figure(float x1_, float x2_, float y1_, float y2_, GLuint tex_, float alpha_)
{
    x1=x1_;
    x2=x2_;
    y1=y1_;
    y2=y2_;
    tex=tex_;
    alpha=alpha_;
}

void Figure :: draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
        glPushMatrix();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1, 1, 1, alpha);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f((x1-startx)*scrol, (y1-starty)*scrol);
            glTexCoord2f(1, 0); glVertex2f((x2-startx)*scrol, (y1-starty)*scrol);
            glTexCoord2f(1, 1); glVertex2f((x2-startx)*scrol, (y2-starty)*scrol);
            glTexCoord2f(0, 1); glVertex2f((x1-startx)*scrol, (y2-starty)*scrol);
        glEnd();

        glDisable(GL_BLEND);

        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Figure :: draw_state()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
        glPushMatrix();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1, 1, 1, alpha);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(x1, y1);
            glTexCoord2f(1, 0); glVertex2f(x2, y1);
            glTexCoord2f(1, 1); glVertex2f(x2, y2);
            glTexCoord2f(0, 1); glVertex2f(x1, y2);
        glEnd();

        glDisable(GL_BLEND);

        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

float Figure :: dist()
{
    float x1_=(x1-startx)*scrol;
    float x2_=(x2-startx)*scrol;
    float y1_=(y1-starty)*scrol;
    float y2_=(y2-starty)*scrol;

    float res=100000;

    res=min(res,dist_(x1_,y1_,mousex,mousey));
    res=min(res,dist_(x1_,y2_,mousex,mousey));
    res=min(res,dist_(x2_,y1_,mousex,mousey));
    res=min(res,dist_(x2_,y2_,mousex,mousey));
    return(res);
}

float Figure :: centre_dist()
{
    float x1_=(x1-startx)*scrol;
    float x2_=(x2-startx)*scrol;
    float y1_=(y1-starty)*scrol;
    float y2_=(y2-starty)*scrol;

    float x=(x1_+x2_)/2.0;
    float y=(y1_+y2_)/2.0;

    return(dist_(x,y,mousex,mousey));
}

bool Figure :: in()
{
    return(x1<=mousex && mousex<=x2 && y1<=mousey && mousey<=y2);
}

bool Figure :: in_dinamic()
{
    return((x1-startx)*scrol<=mousex && mousex<=(x2-startx)*scrol && (y1-starty)*scrol<=mousey && mousey<=(y2-starty)*scrol);

}



bool Figure :: in_circle()
{
    float x1_=(x1-startx)*scrol;
    float x2_=(x2-startx)*scrol;
    float y1_=(y1-starty)*scrol;
    float y2_=(y2-starty)*scrol;

    return(dist_((x2_+x1_)/float(2.0),(y2_+y1_)/float(2.0),float(mousex),float(mousey))<=(x2_-x1_)/2.0+10.0);
}

void Figure :: resize_(float len)
{
    float sx=(x1+x2)/2.0;
    float sy=(y1+y2)/2.0;

    x1=sx-len/2.0;
    x2=sx+len/2.0;
    y1=sy-len/2.0;
    y2=sy+len/2.0;
}

Circle_element :: Circle_element()
{
    shade=0.0;
}

Circle_element :: Circle_element(float x, float y)
{
    f=Figure(x-20.0,x+20.0,y-20.0, y+20.0, empty_, 0.3);
    R=0.0;
    U=0.0;
    shade=0.0;
}

Circle_element :: Circle_element(Figure f_, float R_, float U_)
{
    f=f_;
    R=R_;
    U=U_;
    shade=0.0;
}

void Circle_element :: draw()
{
    glLineWidth(5);
    glColor4f(0, 0, 0, 1);
    for (int i=0;i<reb.size();i++)
    {
        Figure now=object[reb[i].first][reb[i].second].f;
        float x=(now.x1+now.x2)/2.0;
        float y=(now.y1+now.y2)/2.0;
        glBegin(GL_LINES);
            glVertex2f(((f.x1-startx)*scrol+(f.x2-startx)*scrol)/2.0,((f.y2-starty)*scrol+(f.y1-starty)*scrol)/2.0);
            glVertex2f(((x-startx)*scrol+((f.x1-startx)*scrol+(f.x2-startx)*scrol)/2.0)/2.0,((y-starty)*scrol+((f.y2-starty)*scrol+(f.y1-starty)*scrol)/2.0)/2.0);

        glEnd();
    }
    f.draw();

    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0, shade);

    glBegin(GL_QUADS);
        glVertex2f((f.x1-startx)*scrol, (f.y1-starty)*scrol);
        glVertex2f((f.x2-startx)*scrol, (f.y1-starty)*scrol);
        glVertex2f((f.x2-startx)*scrol, (f.y2-starty)*scrol);
        glVertex2f((f.x1-startx)*scrol, (f.y2-starty)*scrol);
    glEnd();

    glDisable(GL_BLEND);

    glPopMatrix();

}

Button :: Button()
{

}

Button :: Button(Figure f_, vector<bool*> change_)
{
    f=f_;
    change=change_;
}

void Button :: draw_state()
{
    f.draw_state();

    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0, shade);

    glBegin(GL_QUADS);
        glVertex2f(f.x1, f.y1);
        glVertex2f(f.x2, f.y1);
        glVertex2f(f.x2, f.y2);
        glVertex2f(f.x1, f.y2);
    glEnd();

    glDisable(GL_BLEND);

    glPopMatrix();
}

void Button :: press_down()
{
    shade=0.3;
}

void Button :: press_up()
{

    if (used)
        shade=0.0; else
        shade=0.16;
    used=!used;
    for (int i=0;i<change.size();i++)
        (*change[i])=!(*change[i]);

}

Button_do :: Button_do()
{

}

Button_do :: Button_do(Figure f_, int (*to_do_)())
{
    f=f_;
    to_do=to_do_;
}

void Button_do :: draw_state()
{
    f.draw_state();
        glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0, shade);

    glBegin(GL_QUADS);
        glVertex2f(f.x1, f.y1);
        glVertex2f(f.x2, f.y1);
        glVertex2f(f.x2, f.y2);
        glVertex2f(f.x1, f.y2);
    glEnd();

    glDisable(GL_BLEND);

    glPopMatrix();
}


void Button_do :: press_down()
{
    shade=0.3;
}

void Button_do :: press_up()
{
    shade=0.0;
    if (f.in())
        (*to_do)();
}


Event :: Event()
{

}

Event :: Event(pair<int,int> p1_, pair<int,int> p2_)
{
    type=1;
    p1=p1_;
    p2=p2_;
}

Event :: Event(pair<int,int> p1_, pair<int,int> p2_, int type_)
{
    type=type_;
    p1=p1_;
    p2=p2_;
}

Event :: Event(Circle_element was_, Circle_element become_, pair<int,int> p_)
{
    type=2;
    was=was_;
    become=become_;
    p1=p_;
}
