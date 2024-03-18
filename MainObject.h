#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46

class MainObject : public BaseObject {

public:
    MainObject();
    ~MainObject();

    void HandleInputAction(SDL_Event events);
    void HandleMove();

private:
    //the hien cho su nhanh cham cua vat
    int x_val_;// gia tri tdoi theo chieu ngang(bien thien)
    int y_val_; // gia tri tdoi theo chieu doc(bien thien)
    int speed;
};

#endif // MAIN_OBJECT_H_
