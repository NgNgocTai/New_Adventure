#include "BaseObject.h"

BaseObject::BaseObject() {
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject() {
    free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen) {

    free();

    SDL_Texture* texture_ =NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
       texture_= SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (texture_ == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    p_object_ = texture_;
    return p_object_ != NULL;
}

void BaseObject::free() {
    if (p_object_!= NULL) {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w=0;
        rect_.h=0;
    }
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) {
    SDL_Rect renderquad ={rect_.x,rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::SetRect(const int& x, const int& y) {
    rect_.x = x;
    rect_.y = y;
}
void BaseObject::SetRectSize(const int& w, const int& h) {
    rect_.w = w;
    rect_.h = h;
}

SDL_Rect BaseObject::GetRect() const {
    return rect_;
}

SDL_Texture* BaseObject::GetObject() const {
    return p_object_;
}
