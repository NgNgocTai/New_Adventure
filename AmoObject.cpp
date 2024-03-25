
#include "AmoObject.h"

AmoObject :: AmoObject()
{
    p_object_ = NULL;
    rect_.x=0;
    rect_.y=0;

    int x_val_ =0;
    int y_val_=0;
    is_move_=false;
    amo_type_ =NONE;
}

AmoObject :: ~AmoObject()
{

}

void AmoObject :: HandleMove(const int&x_border,const int&y_border)
{
    rect_.x+=x_val_;
    if(rect_.x>x_border)is_move_=false;

}

void AmoObject:: HandleInputAction(SDL_Event events)
{

}
