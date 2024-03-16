
#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <string>

// Kích thước màn hình
static const int SCREEN_WIDTH = 1200;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_BPP = 32;

// Các biến toàn cục
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

// Màu chính làm màu nền trong hình ảnh
static const int COLOR_KEY_R = 167;
static const int COLOR_KEY_G = 175;
static const int COLOR_KEY_B = 180;

// Hàm khởi tạo và giải phóng
bool init(); // Khởi tạo SDL và cửa sổ
SDL_Texture* loadTexture(std::string path); // Tải texture từ đường dẫn ảnh
bool loadMedia(); // Tải tất cả các tài nguyên cần thiết
void close(); // Giải phóng bộ nhớ và thoát khỏi SDL

#endif // COMMONFUNC_H
