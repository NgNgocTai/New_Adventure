

#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

#include "Common_Function.h"
#include "BaseObject.h"

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33
class ThreatObject : public BaseObject
{
public:

    ThreatObject();
    ~ThreatObject();
    //Xu ly di chuyen
    void HandleMove(const int& x_border,const int& y_border );
    void HandleInputAction(SDL_Event events);

    //Setter va Getter cho x_val, y_val
    void set_x_val(const int& x){x_val_=x;}
    void set_y_val(const int &y){y_val_=y;}

    int get_x_val() const{return x_val_;}
    int get_y_val() const {return y_val_;}

private:
    int x_val_;
    int y_val_;

};


#endif // THREAT_OBJECT_H
