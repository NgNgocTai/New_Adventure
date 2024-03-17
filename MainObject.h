
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"

#define WIDTH_MAIN_OBJECT 64
#define HEIGHT_MAIN_OBJECT 91

class MainObject : public BaseObject {

public:
    MainObject();
    ~MainObject();

    void HandleInputAction(SDL_Event events);
    void HandleMove();

private:
    int x_val_;// gia tri tdoi theo chieu ngang
    int y_val_; // gia tri tdoi theo chieu doc
};

#endif // MAIN_OBJECT_H_
