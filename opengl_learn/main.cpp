#include "includes.h"
#include "load_textures.h"
#include "basik_classes.h"
#include "feel_draw.h"
#include "feel_reaction.h"
#include "undo_redo.h"
#include "object_menu_draw.h"
#include "object_menu_reaction.h"
#include "delete_mode_reaction.h"
#include "input_info.h"
#include "read_write.h"

void Draw()
{


    glClear(GL_COLOR_BUFFER_BIT);
    if (in_feel)
    {
        draw_feel();
        draw_left_menu();
        if (object_menu_used)
            object_menu_draw();
        if (input_info_mode)
            input_info_draw();
    }

    glutSwapBuffers();
}


void keyboard(unsigned char c, int x, int y)
{
    if (object_menu_used)
    {
        object_menu_keyboard(c,x,y);
    }
    if (c=='q') exit(0);
    if (input_info_mode)
    {
        input_keyboard(c);
    }


    if (object_menu_used) return;
    switch (c)
    {
        case 'r':

            undo();
            break;
        case 't':
            redo();
            break;
        case 'q':
            exit(0);
            break;
        case '+':
            if ((-startx)*min(double(2.0),scrol*speed_scrol)>left_menu_size)
            {
                startx=-left_menu_size/min(double(2.0),scrol*speed_scrol);
                startx=min(startx,feel_seg_size*feel_size-WinWid/scrol);
            }
            if ((-startx)*scrol<left_menu_size)
            {
                scrol*=speed_scrol;
                scrol=min(scrol,double(2.0));
            }
            break;
        case '-':
            if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol>WinWid && (feel_size*feel_seg_size-starty)*scrol/speed_scrol>WinHei)
            {
                scrol/=speed_scrol;
            } else
            {
                if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol<=WinWid)
                {
                    startx=feel_size*feel_seg_size-(WinWid/(scrol/speed_scrol))-0.0001;
                    startx=max(double(-left_menu_size)/scrol,startx);
                }

                if ((feel_size*feel_seg_size-starty)*scrol/speed_scrol<=WinHei)
                {
                    starty=feel_size*feel_seg_size-(WinHei/(scrol/speed_scrol))-0.0001;
                    starty=max(double(0.0),starty);
                }

                if ((feel_size*feel_seg_size-startx)*scrol/speed_scrol>=WinWid && (feel_size*feel_seg_size-starty)*scrol/speed_scrol>=WinHei)
                {
                    scrol/=speed_scrol;
                }
            }
            break;
        default:
            break;
    }
}

void skeyboard(int c, int x, int y)
{

    if (input_info_mode)
    {
        input_skeyboard(c);
    }
    if (input_info_mode) return;
    if (object_menu_used) return;
    switch (c)
    {
        case GLUT_KEY_RIGHT:
            startx+=speed_move;
            startx=min(startx,feel_seg_size*feel_size-WinWid/scrol);
            break;

        case GLUT_KEY_LEFT:
            startx-=speed_move;
            startx=max(double(-left_menu_size)/scrol,startx);
            break;
        case GLUT_KEY_DOWN:
            starty+=speed_move;
            starty=min(starty,feel_seg_size*feel_size-WinHei/scrol);
            break;
        case GLUT_KEY_UP:
            starty-=speed_move;
            starty=max(double(0.0),starty);
            break;
        default:
            break;
    }

}



void creat_feel()
{
    //cout<<WinWid<<'!'<<' '<<WinHei<<'\n';
    for (int i=0;i<feel_size;i++)
        for (int j=0;j<feel_size;j++)
        if (rand()%3)
        feel_background.push_back(Figure(feel_seg_size*i, feel_seg_size*(i+1), feel_seg_size*j, feel_seg_size*(j+1), feel_background_texture[0],1)); else
        feel_background.push_back(Figure(feel_seg_size*i, feel_seg_size*(i+1), feel_seg_size*j, feel_seg_size*(j+1), feel_background_texture[1],1));

    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            object[i][j]=Circle_element(i*feel_seg_size,j*feel_seg_size);

    left_menu_background=Figure(0,left_menu_size,0,WinHei,left_menu_background_tex,1.0);

    for (int i=0;i<7;i++)
        left_menu_vertical[i]=Figure(0,left_menu_size/2.0,100+i*(WinHei-100)/7.0,100+(i+1)*(WinHei-100)/7.0,left_menu_vertical[i].tex,1.0);

    for (int i=0;i<7;i++)
        left_menu_horizontal[i]=Figure(left_menu_size/2.0,left_menu_size,100+i*(WinHei-100)/7.0,100+(i+1)*(WinHei-100)/7.0,left_menu_horizontal[i].tex,1.0);
    line_mode=Button(Figure(50,left_menu_size,50,100,line_mode_tex,1.0),{&line_mode_used});
    point_mode=Button(Figure(0,50,50,100,point_mode_tex,1.0),{&point_mode_used});
    move_mode=Button(Figure(100,150,0,50,move_tex,1.0),{&move_mode_used});
    delete_mode=Button(Figure(150,200,0,50,delete_mode_tex,1.0),{&delete_mode_used});
    undo_button=Button_do(Figure(0,50,0,50,undo_tex,1.0),&undo);
    redo_button=Button_do(Figure(50,100,0,50,redo_tex,1.0),&redo);
    shade_button1.tex=shade_button_tex1;
    shade_button2.tex=shade_button_tex2;

    double w1=WinWid/2.3;
    double h1=WinHei/2.3;
    double w2=WinWid/2.5+100;
    double h2=WinHei/2.5+100;
    double l=(WinWid-w1*2)/2.0;

    input_info_background=Figure(w1,WinWid-w1,h1,WinHei-h1,info_background,1.0);
    input_feel=Figure(w2,WinWid-w2,h2,h2+25,text_line,1.0);
    input_ok=Button_do(Figure(w1,w1+l,WinHei-h1,WinHei-h1+100,ok_tex,1.0),&input_ok_do);
    input_R_ok=Button_do(Figure(w1,w1+l,WinHei-h1,WinHei-h1+100,ok_tex,1.0),&change_R);
    input_bad=Button_do(Figure(w1+l,w1+2*l,WinHei-h1,WinHei-h1+100,bad_tex,1.0),&input_bad_do);

    window_shade=Figure(0,WinWid,0,WinHei,window_shade.tex,0.0);
}

void Initialize(int w, int h)
{
    glViewport(0,0,w,h);
    real_WinWid=w;
    real_WinHei=h;
    WinWid=1920;
    WinHei=1080;
    kx=real_WinWid/WinWid;
    ky=real_WinHei/WinHei;
    //cout<<WinWid<<' '<<WinHei<<' '<<real_WinWid<<' '<<real_WinHei<<'\n';
    left_menu_size=(WinHei-100)/7.0*2.0;
    startx=-left_menu_size;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WinWid, WinHei, 0.0, 0.f, -1.f);

	glMatrixMode(GL_MODELVIEW);

	creat_feel();

}



void mouse_pressed(int button, int state, int x, int y)
{
    x/=kx;
    y/=ky;
    if (in_feel && delete_mode_used)
    {
        delete_mode_mouse_pressed_motion(mousex,mousey,x,y);
    }
    mousex=x;
    mousey=y;
    if (in_feel)
    {
        if (input_info_mode)
        {
            input_info_mouse_pressed(button,state);
            return;
        }

        if (object_menu_used)
        {
            object_menu_mouse_pressed(button,state);
            return;
        }

        if (delete_mode_used)
        {
            delete_mode_mouse_pressed(button,state);
            return;
        }

        if (line_mode_used && mousex>left_menu_size)
            add_point_to_choosen();

        if (mousex<=left_menu_size)
            left_menu_mouse_pressed(button,state); else
            feel_mouse_pressed(button,state);

    }
}

void mouse_pressed_motion(int x, int y)
{

    x/=kx;
    y/=ky;
    if (in_feel && delete_mode_used)
    {
        delete_mode_mouse_pressed_motion(mousex,mousey,x,y);
    }

    mousex=x;
    mousey=y;
    if (in_feel)
    {
        if (line_mode_used && mousex>left_menu_size)
            add_point_to_choosen();
    }

}

void mouse_motion(int x, int y)
{

    x/=kx;
    y/=ky;
    mousex=x;
    mousey=y;
}




void redraw(int)
{

    //cout<<WinWid<<' '<<WinHei<<' '<<real_WinWid<<' '<<real_WinHei<<' '<<left_menu_horizontal[6].y2*ky<<'\n';
    glutPostRedisplay();
    glutTimerFunc(30,redraw,0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);
    ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
    ilutEnable(ILUT_OPENGL_CONV);
    ilutEnable(ILUT_GL_USE_S3TC);


    glutCreateWindow("q");

    load_all();

    glutReshapeFunc(Initialize);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(skeyboard);
    glutTimerFunc(30, redraw, 0);
    glutMouseFunc(mouse_pressed);
    glutMotionFunc(mouse_pressed_motion);
    glutPassiveMotionFunc(mouse_motion);
    glutFullScreen();
    creat_feel();

	glutMainLoop();

	return 0;
}
