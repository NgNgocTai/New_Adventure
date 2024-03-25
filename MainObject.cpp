#include "MainObject.h"
#include "Common_Function.h"

MainObject::MainObject()
{
    // Khởi tạo vị trí và kích thước của đối tượng
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_MAIN_OBJECT;
    rect_.h = HEIGHT_MAIN_OBJECT;

    // Đặt vận tốc ban đầu bằng 0
    x_val_ = 0;
    y_val_ = 0;
    speed = 3;
}

MainObject::~MainObject()
{
    // Destructor không cần làm gì trong trường hợp này
}

void MainObject::HandleInputAction(SDL_Event events) // Xử lý sự kiện đầu vào (bàn phím/chuột)
{
    // Xử lý sự kiện từ bàn phím
    if (events.type == SDL_KEYDOWN) // Nếu một phím được nhấn xuống
    {
        switch (events.key.keysym.sym) // Kiểm tra phím nào được nhấn
        {
            case SDLK_w:
                y_val_ = -speed; // Di chuyển lên
                break;
            case SDLK_s:
                y_val_ = speed; // Di chuyển xuống
                break;
            case SDLK_d:
                x_val_ = speed; // Di chuyển sang phải
                break;
            case SDLK_a:
                x_val_ = -speed; // Di chuyển sang trái
                break;
            default:
                break;
        }
    }
    else if (events.type == SDL_KEYUP) // Nếu một phím được thả ra
    {
        switch (events.key.keysym.sym) // Kiểm tra phím nào được thả ra
        {
            case SDLK_w:
                y_val_ = 0; // Dừng di chuyển lên
                break;
            case SDLK_s:
                y_val_ = 0; // Dừng di chuyển xuống
                break;
            case SDLK_d:
                x_val_ =0; // Dừng di chuyển sang phải
                break;
            case SDLK_a:
                x_val_ = 0; // Dừng di chuyển sang trái
                break;
            default:
                break;
        }
    }
    // Xử lý sự kiện từ chuột
    else if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        AmoObject *p_amo  = new AmoObject();
        if(events.button.button==SDL_BUTTON_LEFT)
        {

             p_amo->SetWidthHeight(WIDTH_LASER,HEIGHT_LASER);
             p_amo->LoadImg("picture/laser.png",gRenderer);
             p_amo->set_type(AmoObject::LASER);
        }
        else if(events.button.button==SDL_BUTTON_RIGHT)
         {
             p_amo->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
             p_amo->LoadImg("picture/sphere.png",gRenderer);
             p_amo->set_type(AmoObject::SPHERE);
        }
        p_amo ->SetRect(this->rect_.x +WIDTH_MAIN_OBJECT-30 ,this->rect_.y+HEIGHT_MAIN_OBJECT*0.5);
        p_amo ->set_x_val_(10);
        p_amo ->set_is_move(true);

        p_amo_list.push_back(p_amo);
        p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else if (events.type == SDL_MOUSEBUTTONUP)
    {

    }
    else { ; } // Không thực hiện hành động nào cho các loại sự kiện khác
}

void MainObject::HandleAmo(SDL_Renderer* des )
{
    for(int i=0;i<p_amo_list.size();i++){
        AmoObject *p_amo = p_amo_list.at(i);
        if(p_amo !=NULL){
            if(p_amo->get_is_move()==true)
            {
               p_amo->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
               p_amo->Render(des);

            }
            else
            {
                p_amo_list.erase(p_amo_list.begin()+i);
                if(p_amo!=NULL)
                {   delete p_amo;
                    p_amo=NULL;
                }
            }
        }
    }
}
void MainObject::HandleMove()
{


    // Cập nhật vị trí của đối tượng dựa trên vận tốc của nó, nhân với hệ số giảm tốc độ
    rect_.x += x_val_ ;
    rect_.y += y_val_ ;

    // Kiểm tra xem đối tượng có ra khỏi ranh giới của màn hình không và điều chỉnh vị trí của nó nếu cần
    if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
        rect_.x -= x_val_ ;

    if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 100)
        rect_.y -= y_val_ ;
}
