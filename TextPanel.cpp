/* 
 * File:   TextPanel.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:44 AM
 */

#include "flags.h"
#include "resources.h"
#include "TextPanel.h"


TextPanel::TextPanel(const string text)
{

    const ResAnim *p_res_panel = res::resources.getResAnim("panel");
    setResAnim(p_res_panel);
    setGuides(TILE_WIDTH, TILE_WIDTH, TILE_HEIGHT, TILE_HEIGHT);

    text_field = new TextField;
    text_field->setFont(res::resources.getResFont("pixograd"));
    //text_field->setAlign(TextStyle::VerticalAlign::VALIGN_BASELINE, TextStyle::HorizontalAlign::HALIGN_LEFT);
    text_field->setColor(Color(Color::Thistle));
    text_field->setFontSize(14);
    text_field->setPosition(TILE_WIDTH, 11.f);
    addChild(text_field);

    // Ok button
    ok_btn = new Btn("close_button");
    ok_btn->setPosition(50.f, 20.f);
    // ok_btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &TextPanel::on_ok_click));
    addChild(ok_btn);

    setText(text);
}


TextPanel::TextPanel(const TextPanel& orig)
{
}


TextPanel::~TextPanel()
{
}


void TextPanel::sizeChanged(const Vector2& size)
{
    Box9Sprite::sizeChanged(size);

    if(ok_btn)
    {
        ok_btn->setX(size.x - 13.f);
        ok_btn->setY(-4.f);
    }
}


void TextPanel::setText(const string& text)
{
    text_field->setText(text);

    RectF b;
    text_field->getBounds(b);

    //setPosition(b.pos);
    b.size.x += TILE_WIDTH * 2.f;
    b.size.y += TILE_HEIGHT * 2.f;
    setSize(b.size);
}
