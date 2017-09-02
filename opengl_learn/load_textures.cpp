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
    feel_background_texture[0]=Load("e1.jpg");
    feel_background_texture[1]=Load("e2.jpg");
    empty_=Load("white_circle.png");
    connection_point=Load("black_circle.png");
    put=Load("button_form.png");
    choosen_point_tex=Load("blue_circle.png");
}
