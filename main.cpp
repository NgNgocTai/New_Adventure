
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
    bool ret1 = background.LoadImg("picture/bg1.png", gRenderer);
    if (!ret1) return 0;

    // Tạo đối tượng nhân vật
    MainObject plane_object;
    bool ret2 = plane_object.LoadImg("picture/plane_fly1.png", gRenderer);
    if (!ret2) return 0;
    plane_object.SetRect(100, 200); // Thiết lập vị trí ban đầu của nhân vật
    //plane_object.SetRectSize(80,46);// Thiết lập kích thước ban đầu của nhân vật

    //Tạo đối tượng hiểm họa
    ThreatObject *p_threat =new ThreatObject();// Tạo mối hiểm họa mới
    bool ret3 = p_threat->LoadImg("picture/threat.png",gRenderer);
    if(!ret3)return 0;
    p_threat->SetRect(SCREEN_WIDTH, rand()%300);// Set vị trí ngẫu nhiên đầu tiên
    p_threat->set_x_val(3);

    p_threat ->CreateAmo();// Tạo Amo

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

        // Xử lý di chuyển của nhân vật
        plane_object.HandleMove();


        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render background
        background.Render(gRenderer);

        // Render character
        plane_object.Render(gRenderer);

        // Xử lý di chuyển của các đạn( bắt buộc phải để sau background và plane_object)
        plane_object.HandleAmo(gRenderer);

        //Render Threat

        p_threat -> Render(gRenderer);//Render ThreatObject
        p_threat -> HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);// Xử lí di chuyển ThreatObject
        p_threat -> FireAmo(gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT);// bắn đạn
        // Update screen
        SDL_RenderPresent(gRenderer);
        SDL_Delay(12);
    }

    // Giải phóng các resource và đóng SDL
    close();

    return 0;
}
