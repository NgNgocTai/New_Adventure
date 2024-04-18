
#ifndef AMO_OBJECT_H
#define AMO_OBJECT_H

#include "BaseObject.h"
#include "Common_Function.h"
#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10

// Lớp AmoObject là lớp con của BaseObject, đại diện cho đối tượng đạn
class AmoObject : public BaseObject
{

public :


    // Hàm khởi tạo và hàm hủy
    AmoObject();
    ~AmoObject();

    // Xử lý sự kiện nhập từ bàn phím
    void HandleInputAction(SDL_Event events);

    // Xử lý di chuyển của đạn
    void HandleMove(const int&x_border,const int&y_border);

     // Xử lý di chuyển của đạn của địch
    void HandleMove2();

    //Xử lí di chuyển đạn của boss
    void HandleMove3();

    // Getter và setter cho trạng thái di chuyển của đạn
    bool get_is_move()  const{return is_move_;}
    void set_is_move(const bool& move) {is_move_ = move;}

    // Thiết lập chiều rộng và chiều cao của đạn
    void SetWidthHeight(const int& width, const int& height) {rect_.w = width; rect_.h = height;}

    //Getter và setter cho tốc độ đạn
    int  get_x_val_ ()const {return x_val_;}
    void set_x_val_(const int& x)  {x_val_=x;}

private:
    int x_val_; // Giá trị tốc độ theo chiều ngang
    int y_val_; // Giá trị tốc độ theo chiều dọc
    bool is_move_; // Trạng thái di chuyển của đạn


};

#endif // AMO_OBJECT_H
