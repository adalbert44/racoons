#ifndef BASIK_CLASSES_H_INCLUDED
#define BASIK_CLASSES_H_INCLUDED

    #include "includes.h"

    struct Figure
    {
    public:
        float x1,x2,y1,y2,alpha;
        GLuint tex;

        Figure();
        Figure(float x1_, float x2_, float y1_, float y2_, GLuint tex_, float alpha);
        float dist();
        void draw();
        void draw_state();

    };

    struct Circle_element
    {
    public:
        Figure f;
        float R;
        float U;
        Circle_element();
        Circle_element(float x, float y);
        Circle_element(Figure f_, float R_, float U_);
    };
    extern Circle_element object[30][30];
    extern std::vector<Figure> feel_background;
    extern Figure left_menu_background;
    extern Figure left_menu_vertical[9];
    extern Figure left_menu_horizontal[9];
#endif // BASIK_CLASSES_H_INCLUDED
