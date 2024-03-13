#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL; // Cửa sổ SDL
SDL_Renderer* gRenderer = NULL; // Renderer SDL
SDL_Texture* gBackgroundTexture = NULL; // Texture cho nền
SDL_Texture* gObjectTexture = NULL; // Texture cho đối tượng

// Khởi tạo SDL và cửa sổ
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

// Tạo texture từ một đường dẫn hình ảnh
SDL_Texture* loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Xóa phông xanh cho nhân vật
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 0));

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

// Tải tất cả các tài nguyên cần thiết
bool loadMedia() {
    bool success = true;
    // Tải texture cho nền
    gBackgroundTexture = loadTexture("picture/bg2.png");
    if (gBackgroundTexture == NULL) {
        printf("Failed to load background texture!\n");
        success = false;
    }

    // Tải texture cho đối tượng
    gObjectTexture = loadTexture("human64x91.png");
    if (gObjectTexture == NULL) {
        printf("Failed to load object texture!\n");
        success = false;
    }

    return success;
}

// Giải phóng bộ nhớ và thoát khỏi SDL
void close() {
    SDL_DestroyTexture(gBackgroundTexture);
    gBackgroundTexture = NULL;

    SDL_DestroyTexture(gObjectTexture);
    gObjectTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

// Hàm chính
int main(int argc, char* argv[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_RenderClear(gRenderer);
                SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL); // Render texture cho nền
                SDL_RenderCopy(gRenderer, gObjectTexture, NULL, NULL); // Render texture cho đối tượng
                SDL_RenderPresent(gRenderer); // Hiển thị renderer
            }
        }
    }
    close(); // Đóng SDL
    return 0;
}
