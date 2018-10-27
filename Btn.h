/* 
 * File:   Btn.h
 * Author: ns
 *
 * Created on October 24, 2018, 10:25 PM
 */

#ifndef BTN_H
#define BTN_H

#include <string>
#include <oxygine-framework.h>


using namespace std;
using namespace oxygine;


DECLARE_SMART(Btn, spBtn);


class Btn : public Button
{
private:
    INHERITED(Button);
public:
    Btn(string button_name);
    Btn(const Btn& orig);
    virtual ~Btn();

};

#endif /* BTN_H */

