



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

void AmoObject :: HandleMove()
{

}

void AmoObject:: HandleInputAction(SDL_Event events)
{

}
