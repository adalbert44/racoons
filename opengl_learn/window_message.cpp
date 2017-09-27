#include "window_message.h"

void window_message_draw()
{
    window_shade.alpha=0.25;
    window_shade.draw_state();
    input_info_background.draw_state();
    double x=input_info_background.x1+20;
    double y=(input_info_background.y1+input_info_background.y2)/2.0+10;
    drawstring(x,y,1.0,window_message_write);
}

void window_message_reaction(int button, int state)
{
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        window_message=0;
        window_message_write="";
    }
}
