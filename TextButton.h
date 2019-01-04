/* 
 * File:   TextButton.h
 * Author: ns
 *
 * Created on January 1, 2019, 11:21 PM
 */

#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <string>
#include <oxygine-framework.h>

using namespace oxygine;
using namespace std;


DECLARE_SMART(TextButton, spTextButton);


class TextButton : public Button
{
private:
    spTextField _text;

public:
    TextButton();
    TextButton(const string);
    TextButton(const TextButton& orig);
    virtual ~TextButton();

    void setText(const string);
};

#endif /* TEXTBUTTON_H */
