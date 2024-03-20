#include <SDL.h>
#include <stdio.h>
#include "BaseObject.h"
#include "Common_Function.h"
#include "MainObject.h"
#include "AmoObject.h"
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
    //plane_object.SetRectSize(WIDTH_MAIN_OBJECT, HEIGHT_MAIN_OBJECT); // Thiết lập kích thước cho hình ảnh

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
        background.Render(gRenderer, NULL);

        // Render character
        plane_object.Render(gRenderer, NULL);

        // Update screen
        SDL_RenderPresent(gRenderer);
        SDL_Delay(12);

    }

    // Giải phóng các resource và đóng SDL
    close();

    return 0;
}
