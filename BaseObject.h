#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "Common_Function.h"

// Lớp BaseObject đại diện cho một đối tượng cơ bản trong trò chơi
class BaseObject {
public:
    BaseObject(); //   Constructor
    ~BaseObject(); // Destructor

    bool LoadImg(std::string path, SDL_Renderer* screen); // Tải hình ảnh và tạo texture
    void SetRect(const int& x, const int& y); // Thiết lập vị trí của đối tượng
    void SetRectSize(const int& w, const int& h); // Thiết lập kích thước của đối tượng
    SDL_Rect GetRect() const; // Lấy vị trí của đối tượng
    SDL_Texture* GetObject() const; // Lấy con trỏ đến texture của đối tượng
    void Render(SDL_Renderer* render, const SDL_Rect* clip = NULL); // Vẽ texture lên renderer
    void Move();
    void free(); // Giải phóng texture

protected:
    SDL_Texture* p_object_; // Texture của đối tượng
    SDL_Rect rect_; // Vị trí và kích thước của đối tượng
};

#endif // BASEOBJECT_H
