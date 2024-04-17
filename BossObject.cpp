


#include "BossObject.h"

//Ham khoi taos
BossObject :: BossObject()
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
BossObject :: ~BossObject()
{
    if(p_amo_list.size()>0)
    {
        for(int i=0;i<p_amo_list.size();i++)
        {
            AmoObject*p_amo=p_amo_list.at(i);
            if(p_amo!=NULL){
                delete p_amo;
                p_amo=NULL;
            }
        }
        p_amo_list.clear();
    }
}
// Hàm tạo ảnh đạn
void BossObject :: CreateAmo()
{
    AmoObject *p_amo = new AmoObject();
    if(p_amo!=NULL)
    {
        bool ret = p_amo -> LoadImg("picture/sphere2.png",gRenderer);
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

void BossObject :: FireAmo(SDL_Renderer* des,const int&x_limit,const int&y_limit)
{
    for(int i=0;i<p_amo_list.size();i++)
    {
        AmoObject *p_amo = p_amo_list.at(i);
        if(p_amo!=NULL)
        {
            // Set cho vật bắn đạn và không bắn thì vị trí <140 (tránh xả đạn lúc cuối)
            if(p_amo->get_is_move()==true && this->rect_.x >140 )
            {
                p_amo->HandleMove2();// Xử lí đạn của ThreatObject
                p_amo ->Render(gRenderer);// Render đạn
            }
            else
            {
                p_amo ->set_is_move(true); // Hồi lại viên đạn về trạng thái bắn true
                p_amo->SetRect(this->rect_.x ,this->rect_.y+rect_.h*0.5);// Đạn đc reset vị trí sau khi đi hết màn hình
            }
        }
    }
}

void BossObject :: HandleMove(const int& x_border,const int& y_border ) // Cho  boss di chuyển lên xuống lung tung
{

}

