

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


private:
    int x_val_; // Giá trị tốc độ theo chiều ngang
    int y_val_; // Giá trị tốc độ theo chiều dọc
    bool is_move_; // Trạng thái di chuyển của đạn
    int amo_type_; // Loại đạn

};

#endif // AMO_OBJECT_H
