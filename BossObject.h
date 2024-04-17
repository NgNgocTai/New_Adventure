

#ifndef BOSSOBJECT_H
#define BOSSOBJECT_H
#include<vector>
#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33

class BossObject : public BaseObject

{
public :
    BossObject();
    ~BossObject();
     // Xử lí di chuyển
     void HandleMove(const int& x_border,const int& y_border );


    //Setter va Getter cho x_val, y_val
    void set_x_val(const int& x){x_val_=x;}
    void set_y_val(const int &y){y_val_=y;}

    int get_x_val() const{return x_val_;}
    int get_y_val() const {return y_val_;}

    // Setter and getter for bullets
    void SetAmoList(std::vector<AmoObject*>amo_list){p_amo_list=amo_list;}
    std::vector<AmoObject*> GetAmoList() const {return p_amo_list;}
    //Tạo đạn
    void CreateAmo();
    //Bắn đạn
    void FireAmo(SDL_Renderer* des,const int&x_limit,const int&y_limit);



private:
    int x_val_;
    int y_val_;

    std::vector <AmoObject*>p_amo_list;// List cac Amo

};


#endif
