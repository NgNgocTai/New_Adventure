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
                //Khi nút space được ấn thì đệ tử bắn đạn (Thực ra vẫn là MainObject bắn thôi :)) )
                case SDLK_SPACE:
                    AmoObject *p_amo  = new AmoObject();
                    p_amo->LoadImg("picture/sphere.png",gRenderer);
                    p_amo->SetRectSize(WIDTH_SPHERE,WIDTH_SPHERE);
                    p_amo ->SetRect(this->rect_.x +WIDTH_MAIN_OBJECT-35 ,this->rect_.y+HEIGHT_MAIN_OBJECT*0.8+40);
                    p_amo ->set_x_val_(10);
                    p_amo ->set_is_move(true);
                    p_amo_list.push_back(p_amo);
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

                 if(!boss_render){
                    p_amo->LoadImg("picture/rocket1.png",gRenderer);

                 }
                 else {
                     p_amo->LoadImg("picture/amo3.png",gRenderer);

                 }

                 p_amo->SetRectSize(36,5);

                 //Mix_PlayChannel(-1, gGun1, 0);// Chạy âm thanh khi ấn chuột
            }
            else if(events.button.button==SDL_BUTTON_RIGHT)
             {

                if(!boss_render)
                 p_amo->LoadImg("picture/rocket2.png",gRenderer);
                else
                 p_amo->LoadImg("picture/amo2.png",gRenderer);
                 p_amo->SetRectSize(72,12);

                 //Mix_PlayChannel(-1, gGun2, 0);// Chạy âm thanh khi ấn chuột
            }
            p_amo ->SetRect(this->rect_.x +WIDTH_MAIN_OBJECT-35 ,this->rect_.y+HEIGHT_MAIN_OBJECT*0.8);
            p_amo ->set_x_val_(10);
            p_amo ->set_is_move(true);
            p_amo_list.push_back(p_amo);

        }
        else if (events.type == SDL_MOUSEBUTTONUP)
        {

        }
        else { ; } // Không thực hiện hành động nào cho các loại sự kiện khác
    }

    // Xử lí đạn
    void MainObject::HandleAmo(SDL_Renderer* des )
    {
        for(int i=0;i<p_amo_list.size();i++){
            AmoObject *p_amo = p_amo_list.at(i);
            if(p_amo !=NULL){
                if(p_amo->get_is_move()==true)
                {
                   p_amo->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);// Xử lí di chuyển
                   p_amo->Render(des);// Render đạn
                }
                else
                {
                     //Xóa đạn vừa bắn ra
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


        // Cập nhật vị trí của đối tượng dựa trên vận tốc của nó
        rect_.x += x_val_ ;
        rect_.y += y_val_ ;

        // Kiểm tra xem đối tượng có ra khỏi ranh giới của màn hình không và điều chỉnh vị trí của nó nếu cần
        if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
            rect_.x -= x_val_ ;

        if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 100)
            rect_.y -= y_val_ ;
    }

   void MainObject::HandleMove_Thienthach()
{
    rect_.y += speed;
    rect_.x-=speed;
    if (rect_.y >= SCREEN_HEIGHT)
    {
        rect_.y = 0;
       int  ranNum = rand() % SCREEN_WIDTH ;
        if(ranNum<100)
            ranNum+=50;
        else if(ranNum>SCREEN_WIDTH-50);
            ranNum-=50;
        rect_.x=ranNum;
    }
}


    //Xóa đạn
    void MainObject::RemoveAmo(const int &idx)
    {
      for(int i=0;i<p_amo_list.size();i++)
      {
          if(idx<p_amo_list.size())
          {
              AmoObject *p_amo=p_amo_list.at(idx);
              p_amo_list.erase(p_amo_list.begin()+idx);

              if(p_amo!=NULL)
              {
                  delete p_amo;
                  p_amo =NULL;
              }

          }
      }


    }
