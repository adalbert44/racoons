#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED

    #include "includes.h"
    #include "input_text.h"
    #include "read_write.h"
    #include "get_power.h"

    void main_menu_draw();
    void main_menu_reaction(int button, int state);
    int create_new_file();
    int load_old_file();
    int exit_();

#endif // MAIN_MENU_H_INCLUDED
