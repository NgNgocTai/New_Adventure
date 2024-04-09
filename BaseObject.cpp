#include "BaseObject.h"

bool is_run_screen =true;
BaseObject::BaseObject() {
    // Khởi tạo con trỏ texture và khung hình rect
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject() {
    // Hủy giải phóng bộ nhớ khi đối tượng được hủy
    free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen) {
    // Giải phóng trước khi tải ảnh mới
    free();

    // Tải ảnh từ đường dẫn path
    SDL_Texture* texture_ = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Không thể tải ảnh %s! Lỗi SDL_image: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Thiết lập màu chính để làm màu trong suốt
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        // Tạo texture từ surface
        texture_ = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (texture_ == NULL) {
            printf("Không thể tạo texture từ %s! Lỗi SDL: %s\n", path.c_str(), SDL_GetError());
        } else {
            // Cập nhật kích thước rect
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    // Lưu texture vào con trỏ của đối tượng
    p_object_ = texture_;
    return p_object_ != NULL;
}

void BaseObject::free() {
    // Giải phóng texture nếu tồn tại
    if (p_object_ != NULL) {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
// SDL_Rect* : phần trên màn bạn muốn vẽ, nếu là NULL thì toàn bộ Texture được vẽ
//SDL_Rect : lưu vị trí x,y và kích thước w,h hình muốn vẽ
void BaseObject::Render(SDL_Renderer* render, const SDL_Rect* clip) {
    // Render đối tượng lên màn hình
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(render, p_object_, clip, &renderquad);
}

void BaseObject::SetRect(const int& x, const int& y) {
    // Thiết lập vị trí của rect
    rect_.x = x;
    rect_.y = y;
}

void BaseObject::SetRectSize(const int& w, const int& h) {
    // Thiết lập kích thước của rect

    rect_.w = w;
    rect_.h = h;
}
SDL_Rect BaseObject::GetRect() const {
    // Trả về rect của đối tượng
    return rect_;
}

void BaseObject ::Move(){
    if(is_run_screen)
   {
        rect_.x-=SCREEN_SPEED;
        if(rect_.x<=-(WIDTH_BACKGROUND-SCREEN_WIDTH))
        {
            is_run_screen=false;

        }

   }

}

SDL_Texture* BaseObject::GetObject() const {
    // Trả về texture của đối tượng
    return p_object_;
}
