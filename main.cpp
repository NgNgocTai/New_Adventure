
#include <SDL.h>
#include <stdio.h>
#include "BaseObject.h"
#include "Common_Function.h"

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
    BaseObject character;
    bool ret2 = character.LoadImg("picture/plane_fly1.png", gRenderer);
    if (!ret2) return 0;

    character.SetRect(300, 420);
    character.SetRectSize(64, 91); // Thiết lập kích thước cho hình ảnh
    // Main loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render background
        background.Render(gRenderer, NULL);

        // Render character
        character.Render(gRenderer, NULL);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    // Giải phóng các resource và đóng SDL
    close();

    return 0;
}
