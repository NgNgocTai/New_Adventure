
#include "AmoObject.h"

AmoObject :: AmoObject()
{
    p_object_ = NULL;
    rect_.x=0;
    rect_.y=0;

    int x_val_ =0;
    int y_val_=0;
    is_move_=false;

}

AmoObject :: ~AmoObject()
{

}
//Xử lí đạn của MainObject
void AmoObject :: HandleMove(const int&x_border,const int&y_border)
{
    rect_.x+=x_val_;
    if(rect_.x>x_border)is_move_=false;

}

 // Xử lý di chuyển của đạn địch
void AmoObject :: HandleMove2()

{
    rect_.x -=x_val_;
    if(rect_.x <0)is_move_=false;
}
//Xử lí di chuyển ảo ma của đạn Boss
void AmoObject::HandleMove3()
{

    static bool moving_up =true;
    if(moving_up)
    {
        rect_.x-=x_val_/2;
        rect_.y-=x_val_;
        if(rect_.y<=0)
        {
            moving_up=false;
        }
    }
    else
    {
        rect_.x-=x_val_/2;
        rect_.y+=x_val_;
        if(rect_.y>=SCREEN_HEIGHT-100)
        {
            moving_up=true;
        }
    }
    if(rect_.x <0)is_move_=false;

}


void AmoObject:: HandleInputAction(SDL_Event events)
{

}
