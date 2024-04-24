#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"

#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52


#include <vector>


class MainObject : public BaseObject {

public:
    MainObject();
    ~MainObject();

    void HandleInputAction(SDL_Event events);// Xử lý sự kiện đầu vào (bàn phím/chuột)
    void HandleMove();// Xử lí di chuyển vật
    void HandleMove_Thienthach();// Xử lí di chuyển thiên thạch
    void HandleAmo(SDL_Renderer* des );// Xử lí đạn
    void SetAmoList(std::vector<AmoObject*>amo_list){p_amo_list=amo_list;}
    std::vector<AmoObject*> GetAmoList() const {return p_amo_list;}
    void RemoveAmo(const int &idx);//xóa đạn

private:
    int x_val_;// gia tri tdoi theo chieu ngang(bien thien)
    int y_val_; // gia tri tdoi theo chieu doc(bien thien)
    int speed;// toc do bay

    std::vector <AmoObject*>p_amo_list;// List cac Amo


};

#endif // MAIN_OBJECT_H_
