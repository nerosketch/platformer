/* 
 * File:   TextPanel.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:44 AM
 */

#ifndef BASEINTERFACE_H
#define BASEINTERFACE_H

#include <string>
#include <oxygine-framework.h>
#include "base.h"
#include "Btn.h"


using namespace std;
using namespace oxygine;


DECLARE_SMART(TextPanel, spTextPanel);


class TextPanel : public Base, public Box9Sprite
{
private:
    INHERITED(Box9Sprite);
    spTextField text_field;

public:
    TextPanel(const string text);
    TextPanel(const TextPanel& orig);
    virtual ~TextPanel();

    void setText(const string& text);

    void sizeChanged(const Vector2& size) override;

    spBtn ok_btn;
};

#endif /* BASEINTERFACE_H */
