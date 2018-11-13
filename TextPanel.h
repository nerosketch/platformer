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


using namespace std;
using namespace oxygine;


DECLARE_SMART(TextPanel, spTextPanel);


class TextPanel : public Base, public Actor
{
private:
    INHERITED(Actor);
    spTextField text_field;
    spSprite borders[9];

public:
    TextPanel(const string text);
    TextPanel(const TextPanel& orig);
    virtual ~TextPanel();

    void setText(string text);

    void sizeChanged(const Vector2& size) override;

};

#endif /* BASEINTERFACE_H */
