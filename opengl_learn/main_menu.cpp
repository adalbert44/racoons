#include "main_menu.h"

int create_new_file()
{
    in_feel=1;
    in_main_menu=0;
}

int exit_()
{
    exit(0);
}

void main_menu_draw()
{
    main_menu_background.draw_state();

    new_file.draw_state();
    old_file.draw_state();
    lab.draw_state();
    photo.draw_state();
    exit_b.draw_state();
}


void main_menu_reaction(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (new_file.f.in())
        {
            new_file.press_down();
            pressed_do=&new_file;
        } else
        if (old_file.f.in())
        {
            old_file.press_down();
            pressed_do=&old_file;
        } else
        if (lab.f.in())
        {
            lab.press_down();
            pressed_do=&lab;
        } else
        if (photo.f.in())
        {
            photo.press_down();
            pressed_do=&photo;
        } else
        if (exit_b.f.in())
        {
            exit_b.press_down();
            pressed_do=&exit_b;
        }
    }
    //cout<<new_file.shade<<'\n';
    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (pressed_do!=NULL)
        {
            (*pressed_do).press_up();
            pressed_do=NULL;
        }
    }

}
