#include "element_type.h"

bool voltmetr(GLuint t)
{
    return(t==left_menu_horizontal[1].tex || t==left_menu_vertical[1].tex);
}

bool ampermetr(GLuint t)
{
    return(t==left_menu_horizontal[3].tex || t==left_menu_vertical[3].tex);
}

bool rezistor(GLuint t)
{
    return(t==left_menu_horizontal[0].tex || t==left_menu_vertical[0].tex);
}
