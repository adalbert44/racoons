#include "lab_mode.h"

void lab_mode_draw()
{
    statement_show.draw_state();
}

void lab_mode_reaction(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (statement_show.f.in())
        {
            statement_show.press_down();
            pressed_do=&statement_show;
        }
    }

    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {

        if (pressed_do!=NULL)
        {
            (*pressed_do).press_up();
            pressed_do=NULL;
        }
    }
}

int show_statement()
{

}
