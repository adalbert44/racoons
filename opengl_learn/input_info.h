#ifndef INPUT_INFO_H_INCLUDED
#define INPUT_INFO_H_INCLUDED

    #include "includes.h"
    #include "feel_reaction.h"

    void input_info_draw();
    void input_info_mouse_pressed(int button, int state);
    int input_ok_do();
    int input_bad_do();
    void input_keyboard(unsigned char c);
    void input_skeyboard(unsigned char c);


#endif // INPUT_INFO_H_INCLUDED
