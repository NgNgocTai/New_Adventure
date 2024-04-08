#include <SDL.h>
#include <stdio.h>
#include "BaseObject.h"
#include "Common_Function.h"
#include "MainObject.h"
#include "AmoObject.h"
#include "ThreatObject.h"
int main(int argc, char* argv[]) {

    // Khởi tạo SDL
    if (!init()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    // Tải media cần thiết
    if (!loadMedia()) {
        printf("Failed to load media!\n");
        return -1;
    }

    // Tạo đối tượng background
    BaseObject background;
    bool ret1 = background.LoadImg("picture/bg4800.png", gRenderer);
    if (!ret1) return 0;

    // Tạo đối tượng nhân vật
    MainObject plane_object;
    bool ret2 = plane_object.LoadImg("picture/plane_fly1.png", gRenderer);
    if (!ret2) return 0;
    plane_object.SetRect(100, 200); // Thiết lập vị trí ban đầu của nhân vật
    //plane_object.SetRectSize(80,46);// Thiết lập kích thước ban đầu của nhân vật



    //Tạo mảng các đối tượng hiểm họa
    ThreatObject *p_threats = new ThreatObject [NUM_THREAT];
    for(int i=0;i<NUM_THREAT;i++)
    {
        ThreatObject *p_threat =(p_threats +i);//gán
        if(p_threat!=NULL)
    {
        bool ret3 = p_threat->LoadImg("picture/threat.png",gRenderer);
        if(!ret3)return 0;
        p_threat->SetRect(SCREEN_WIDTH+ i*320, rand()%300);// Set vị trí ngẫu nhiên khác nhau cho từng Object
        p_threat->set_x_val(3);
        p_threat ->CreateAmo();// Tạo Amo
    }
      }
    // Main loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // Xử lý sự kiện
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // Gọi hàm HandleInputAction() của đối tượng plane_object
            plane_object.HandleInputAction(e);
        }


        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render background
        background.Render(gRenderer);

        // Xử lí background di chuyển
        background.Move();

        // Xử lý di chuyển của nhân vật
        plane_object.HandleMove();
        // Render character
        plane_object.Render(gRenderer);

        // Xử lý di chuyển của các đạn( bắt buộc phải để sau background và plane_object)
        plane_object.HandleAmo(gRenderer);



        //Render Threat
        for(int tt=0;tt<NUM_THREAT;tt++)
       {
            ThreatObject *p_threat = (p_threats+tt);
            if(p_threat!=NULL)
           {
                p_threat -> HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);// Xử lí di chuyển ThreatObject
                p_threat -> Render(gRenderer);//Render ThreatObject
                p_threat->FireAmo(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);//Bắn đạn

                //Check va chạm MainObject và Threat
                bool is_col=CheckCollisision(plane_object.GetRect(),p_threat->GetRect());
                if(is_col==true)
                {
                    //Hiện ra thông báo GameOver khi va chạm
                   SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You Lose!", NULL);


                        //Xóa nốt dữ liệu khi kết thúc
                       delete [] p_threats;
                       close();
                       return 0;


                }
                // Check va chạm đạn MainObject với Threat
                std::vector<AmoObject*> amo_list =plane_object.GetAmoList();// Lấy list đạn của MainObject
                for(int im=0;im<amo_list.size();im++)
                {
                    AmoObject* p_amo = amo_list.at(im);
                    if(p_amo!=NULL)
                    {
                        bool is_col2 = CheckCollisision(p_amo->GetRect(),p_threat->GetRect());// bool check va chạm
                        if(is_col2==true)// Khi đạn bắn trúng địch
                        {
                            //Reset vi tri
                            p_threat->Reset(SCREEN_WIDTH+ tt*400, rand()%300);
                            plane_object.RemoveAmo(im);

                        }
                    }
                }

                //Check va chạm đạn Threat với MainObject
                std::vector<AmoObject*> bullet_list =p_threat->GetAmoList();// Lấy list đạn của MainObject
                for(int am=0;am<bullet_list.size();am++)
                {
                    AmoObject* p_amo = bullet_list.at(am);
                    if(p_amo!=NULL)
                    {
                        bool is_col1 = CheckCollisision(p_amo->GetRect(),plane_object.GetRect());// bool check va chạm
                        if(is_col1==true)// Khi đạn bắn trúng MainObject
                        {
                            //Reset vi trí đạn( Có thể viết hàm ResetAmo)

                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", "You Lose!", NULL);

                            //Xóa nốt dữ liệu khi kết thúc
                            delete [] p_threats;
                            close();
                            return 0;


                        }
                    }
                }



           }
       }
        // Update screen
        SDL_RenderPresent(gRenderer);
        SDL_Delay(12);
    }
    delete [] p_threats;

    // Giải phóng các resource và đóng SDL
    close();

    return 0;
}

