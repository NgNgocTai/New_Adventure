
#include "ThreatObject.h"

//Ham khoi taos
ThreatObject :: ThreatObject()
{
    //Set các thông số ban đầu cho ThreatObject
    rect_.x=SCREEN_WIDTH;
    rect_.y=0;
    rect_.w=WIDTH_THREAT;
    rect_.h=HEIGHT_THREAT;

    x_val_=0;
    y_val_=0;

}
//Hàm hủy
ThreatObject :: ~ThreatObject()
{

}
// Hàm tạo ảnh đạn
void ThreatObject :: CreateAmo()
{
    AmoObject *p_amo = new AmoObject();
    if(p_amo!=NULL)
    {
        bool ret = p_amo -> LoadImg("picture/sphere.png",gRenderer);
        if(ret)
        {
            p_amo ->set_is_move(true);// trạng thái viên đạn
            p_amo ->set_type (AmoObject::SPHERE);//loại đạn
            p_amo ->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);// kích thước
            p_amo ->set_x_val_(10);//tốc độ đạn
            p_amo ->SetRect(this->rect_.x ,this->rect_.y+rect_.h*0.5);//vị trí viên đạn
            p_amo_list.push_back(p_amo);
        }
    }
}

void ThreatObject :: FireAmo(SDL_Renderer* des,const int&x_limit,const int&y_limit)
{
    for(int i=0;i<p_amo_list.size();i++)
    {
        AmoObject *p_amo = p_amo_list.at(i);
        if(p_amo!=NULL)
        {
            if(p_amo->get_is_move()==true)
            {
                p_amo->HandleMove2();
                p_amo ->Render(gRenderer);
            }
            else
            {
                p_amo ->set_is_move(true); // Hồi lại viên đạn về trạng thái bắn true
                p_amo->SetRect(this->rect_.x ,this->rect_.y+rect_.h*0.5);// Đạn đc reset vị trí sau khi đi hết màn hình
            }
        }
    }
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
