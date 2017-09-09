#include "load_textures.h"

GLuint Load(std::string b)
{


    GLuint temp = ilLoadImage(b.data());
    glGenTextures(1, &temp);
    glBindTexture (GL_TEXTURE_2D, temp);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return temp;
}







void load_all()
{
    feel_background_texture[0]=Load("textures/e1.jpg");
    feel_background_texture[1]=Load("textures/e2.jpg");
    empty_=Load("textures/white_circle.png");
    connection_point=Load("textures/black_circle.png");
    line_mode_tex=Load("textures/line_mode_tex.png");
    point_mode_tex=Load("textures/point_mode_tex.png");
    choosen_point_tex=Load("textures/blue_circle.png");
    left_menu_background_tex=Load("textures/left_menu_background.png");

    left_menu_vertical[0].tex=Load("textures/left_menu_vertical_0.png");
    left_menu_vertical[1].tex=Load("textures/left_menu_vertical_1.png");
    left_menu_vertical[2].tex=Load("textures/left_menu_vertical_2.png");
    left_menu_vertical[3].tex=Load("textures/left_menu_vertical_3.png");
    left_menu_vertical[4].tex=Load("textures/left_menu_vertical_4.png");
    left_menu_vertical[5].tex=Load("textures/left_menu_vertical_5.png");
    left_menu_vertical[6].tex=Load("textures/left_menu_vertical_6.png");

    left_menu_horizontal[0].tex=Load("textures/left_menu_horizontal_0.png");
    left_menu_horizontal[1].tex=Load("textures/left_menu_horizontal_1.png");
    left_menu_horizontal[2].tex=Load("textures/left_menu_horizontal_2.png");
    left_menu_horizontal[3].tex=Load("textures/left_menu_horizontal_3.png");
    left_menu_horizontal[4].tex=Load("textures/left_menu_horizontal_4.png");
    left_menu_horizontal[5].tex=Load("textures/left_menu_horizontal_5.png");
    left_menu_horizontal[6].tex=Load("textures/left_menu_horizontal_6.png");

    window_shade.tex=Load("textures/black_square.png");
}
