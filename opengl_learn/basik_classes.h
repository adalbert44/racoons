#ifndef BASIK_CLASSES_H_INCLUDED
#define BASIK_CLASSES_H_INCLUDED

    #include "includes.h"
    using namespace std;
    struct Figure

    {
    public:
        float x1,x2,y1,y2,alpha;
        GLuint tex;

        Figure();
        Figure(float x1_, float x2_, float y1_, float y2_, GLuint tex_, float alpha);
        float dist();
        bool in();
        bool in_circle();
        void draw();
        void draw_state();
        void resize_(float siz);


    };

    struct Point
    {
    public:
        float x,y;
        Point()
        {
        }
        Point (float x_, float y_)
        {
            x=x_;
            y=y_;
        }
    };

    struct Circle_element
    {
    public:
        Figure f;
        vector<pair<int,int> > reb;
        float R;
        float U;
        Circle_element();
        Circle_element(float x, float y);
        Circle_element(Figure f_, float R_, float U_);
        void draw();
    };

    class Button
    {
    public:
        Figure f;
        vector<bool*> change;
        float shade=0;
        bool used=0;
        Button();
        Button(Figure f_, vector<bool*> change);
        void draw_state();
        void press_down();
        void press_up();
    };

    extern Circle_element object[30][30];
    extern std::vector<Figure> feel_background;
    extern Figure left_menu_background;
    extern Figure left_menu_vertical[9];
    extern Figure left_menu_horizontal[9];
    extern GLuint taken;
    extern Button line_mode;
    extern bool line_mode_used;
    extern Button point_mode;
    extern bool point_mode_used;
    extern Button* pressed;

#endif // BASIK_CLASSES_H_INCLUDED
