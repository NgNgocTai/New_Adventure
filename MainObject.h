#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46


#include <vector>


class MainObject : public BaseObject {

public:
    MainObject();
    ~MainObject();

    void HandleInputAction(SDL_Event events);
    void HandleMove();
    void SetAmoList(std::vector<AmoObject*>amo_list){p_amo_list=amo_list;}
    void HandleAmo(SDL_Renderer* des );
    std::vector<AmoObject*> GetAmoList() const {return p_amo_list;}
private:
    //the hien cho su nhanh cham cua vat
    int x_val_;// gia tri tdoi theo chieu ngang(bien thien)
    int y_val_; // gia tri tdoi theo chieu doc(bien thien)
    int speed;

    std :: vector <AmoObject*>p_amo_list;


};

#endif // MAIN_OBJECT_H_
