#include "Common_Function.h"

// Khai báo cửa sổ và trình dựng của SDL
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// Hàm khởi tạo SDL và cửa sổ
bool init() {
    // Khởi tạo SDL_VIDEO để sử dụng video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL không thể khởi tạo! Lỗi SDL: %s\n", SDL_GetError());
        return false;
    }

    // Thiết lập chất lượng phóng to và thu nhỏ của renderer
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Tạo cửa sổ SDL với tên "SDL game", kích thước mặc định, và hiển thị
    gWindow = SDL_CreateWindow("SDL game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Không thể tạo cửa sổ! Lỗi SDL: %s\n", SDL_GetError());
        return false;
    }

    // Tạo renderer với phần cứng hỗ trợ và thiết lập màu nền là màu trắng
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Không thể tạo renderer! Lỗi SDL: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Khởi tạo SDL_image để sử dụng PNG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image không thể khởi tạo! Lỗi SDL_image: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

// Hàm tải texture từ tệp hình ảnh
SDL_Texture* loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Không thể tải ảnh %s! Lỗi SDL_image: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Tạo texture từ surface
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
    bool success = true;

    // Không cần thực hiện gì ở đây vì việc tải media được xử lý trong main.cpp

    return success;
}

// Hàm đóng SDL và giải phóng bộ nhớ
void close() {
    // Hủy renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    // Hủy cửa sổ
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Đóng SDL_image và SDL
    IMG_Quit();
    SDL_Quit();
}
