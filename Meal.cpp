#include "Meal.h"
#include <stdlib.h>

Meal::Meal()
{
    //ctor
    x=y=1;
}

void Meal::set_x(const int _x){
    x = _x;
}
void Meal::set_y(const int _y){
    y=_y;
}
void Meal::Sinh(const int xmax, const int ymax){
    set_x(rand()%xmax);
    set_y(rand()%ymax);
}

Meal::~Meal()
{
    //dtor
}
