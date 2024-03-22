
#ifndef AMO_OBJECT_H
#define AMO_OBJECT_H

#include "BaseObject.h"

#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10

// Lớp AmoObject là lớp con của BaseObject, đại diện cho đối tượng đạn
class AmoObject : public BaseObject
{

public :

    // Liệt kê các loại đạn
    enum AmoType
    {
        NONE  =  0, // Không có
        LASER =  1, // Đạn laser
        SPHERE = 2 // Đạn hình cầu
    };

    // Hàm khởi tạo và hàm hủy
    AmoObject();
    ~AmoObject();

    // Xử lý sự kiện nhập từ bàn phím
    void HandleInputAction(SDL_Event events);

    // Xử lý di chuyển của đạn
    void HandleMove();

    // Getter và setter cho loại đạn
    int get_type() {return amo_type_;}
    void set_type(const int& type){amo_type_ = type;}

    // Getter và setter cho trạng thái di chuyển của đạn
    bool get_is_move()  {return is_move_;}
    void set_is_move(bool move) {is_move_ = move;}

    // Thiết lập chiều rộng và chiều cao của đạn
    void SetWidthHeight(const int& width, const int& height) {rect_.w = width; rect_.h = height;}

private:
    int x_val_; // Giá trị tốc độ theo chiều ngang
    int y_val_; // Giá trị tốc độ theo chiều dọc
    bool is_move_; // Trạng thái di chuyển của đạn
    int amo_type_; // Loại đạn

};

#endif // AMO_OBJECT_H
