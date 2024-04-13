#include "Common_Function.h"

// Khai báo cửa sổ và trình dựng của SDL
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;



// Hàm tải texture từ tệp hình ảnh
SDL_Texture* loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Không thể tải ảnh %s! Lỗi SDL_image: %s\n", path.c_str(), IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Không thể tạo texture từ %s! Lỗi SDL: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

// Hàm load media
bool loadMedia() {

    return true;
}

//Hàm check va chạm
bool CheckCollisision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    return (object1.x + object1.w > object2.x &&
            object1.y + object1.h > object2.y + 5 &&
            object2.x + object2.w > object1.x &&
            object2.y + object2.h > object1.y + 5);
}


// Hàm đóng SDL và giải phóng bộ nhớ
void close() {
    // Hủy renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    Mix_FreeChunk(gGun1); gGun1=NULL;
    Mix_FreeChunk(gGun2);gGun2=NULL;

    Mix_FreeChunk(gEx1);gEx1=NULL;
    Mix_FreeChunk(gEx2);gEx2=NULL;
    // Hủy cửa sổ
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Đóng SDL_image và SDL
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
