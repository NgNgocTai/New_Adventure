#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <string>

// Kích thước màn hình

static const int WIDTH_BACKGROUND=4800;
static const int HEIGHT_BACKGROUND=600;
static const int SCREEN_WIDTH = 1200;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_BPP = 32;
static const int SCREEN_SPEED =2;

const int NUM_THREAT = 4; // So luong ThreatObject;

// Các biến toàn cục
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

// Màu chính làm màu nền trong hình ảnh
static const int COLOR_KEY_R = 0;
static const int COLOR_KEY_G = 0xff;
static const int COLOR_KEY_B = 0xff;


// Hàm khởi tạo và giải phóng
bool init(); // Khởi tạo SDL và cửa sổ
SDL_Texture* loadTexture(std::string path); // Tải texture từ đường dẫn ảnh (giong loadImage)
bool loadMedia(); // Tải tất cả các tài nguyên cần thiết
bool CheckCollisision(const SDL_Rect &object1,const SDL_Rect &object2);//check va cham
void close(); // Giải phóng bộ nhớ và thoát khỏi SDL

#endif // COMMONFUNC_H
