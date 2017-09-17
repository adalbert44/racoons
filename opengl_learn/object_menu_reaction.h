#ifndef OBJECT_MENU_REACTION_H_INCLUDED
#define OBJECT_MENU_REACTION_H_INCLUDED

    #include "includes.h"
    #include "delete_mode_reaction.h"

    int object_delete_func();
    int object_rotate_func();
    bool get_dir(GLuint tex);
    void object_menu_mouse_pressed(int button, int state);

#endif // OBJECT_MENU_REACTION_H_INCLUDED



