#ifndef GLOBAL_VARS_H_INCLUDED
#define GLOBAL_VARS_H_INCLUDED

    #include "includes.h"
    #include "basik_classes.h"
    //#include <bits/stdc++.h>

    using namespace std;

    extern float WinWid;
    extern float WinHei;











    extern float speed_scrol;
    extern float speed_move;
    extern float startx;
    extern float starty;
    extern float feel_seg_size;
    extern int feel_size;
    extern float scrol;
    extern float mousex;
    extern float mousey;

    extern int last_event;
    extern GLuint feel_background_texture[2];
    extern GLuint empty_;
    extern float left_menu_size;
    extern bool in_feel;
    extern bool something_taken;
    extern GLuint put;
    extern bool direction;
    extern GLuint connection_point;
    extern vector<pair<int,int> > choosen_point;
    extern GLuint choosen_point_tex;
    extern GLuint left_menu_background_tex;
    extern GLuint line_mode_tex;
    extern GLuint point_mode_tex;
    extern pair<int,int> choosen_object;
    extern bool object_menu_used;
    extern pair<int,int> pred_pos;
    extern GLuint undo_tex;
    extern GLuint redo_tex;
    extern bool choosen_reb[31][31][31][31];
    extern GLuint shade_button_tex1,shade_button_tex2;
    extern void* currentfont;
    extern bool input_info_mode;
    extern int info_i,info_j;
    extern string info_zn;
    extern GLuint delete_mode_tex;
    extern GLuint rotate_tex;

#endif // GLOBAL_VARS_H_INCLUDED
