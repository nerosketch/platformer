/* 
 * File:   TextButton.cpp
 * Author: ns
 * 
 * Created on January 1, 2019, 11:21 PM
 */

#include "resources.h"
#include "TextButton.h"


TextButton::TextButton() :
_text(new TextField)
{
    ResFont *font = res::resources.getResFont("SanasoftHermes");

    _text->setFont(font);
    _text->setFontSize(8);
    _text->setAnchor(0.5f, 0.5f);
    _text->setPosition(8.f, 0.8f);
    _text->setColor(Color::Black);

    addChild(_text);
}


TextButton::TextButton(const string& str) : TextButton()
{
    setText(str);
}


TextButton::TextButton(const TextButton& o) :
_text(o._text)
{}


TextButton::~TextButton()
{}


void TextButton::setText(const string& str)
{
    _text->setText(str);
}
