

#include "ThreatObject.h"

ThreatObject :: ThreatObject()
{
    rect_.x=SCREEN_WIDTH;
    rect_.y=0;
    rect_.w=WIDTH_THREAT;
    rect_.h=HEIGHT_THREAT;

    x_val_=0;
    y_val_=0;

}

ThreatObject :: ~ThreatObject()
{

}

void ThreatObject :: HandleMove(const int& x_border,const int& y_border )
{

    rect_.x -= x_val_;// Di chuyển đều sang trái
    if(rect_.x<0)
    {
        rect_.x =SCREEN_WIDTH;// Set vật về bên phải khi đi hết màn hình

        //Xử lí phần vị trí ngẫu nhiên khi đi hết màn hình
        int random = rand() %400;
        if(random>SCREEN_HEIGHT -200)
        {
            random = SCREEN_HEIGHT*0.4;
        }
        rect_.y=random;
    }
}
void ThreatObject :: HandleInputAction(SDL_Event events)
{

}
