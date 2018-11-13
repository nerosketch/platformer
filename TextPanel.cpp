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
    setPosition(130.f, 130.f);
    //setColor(89, 86, 82, 255);


    const ResAnim *p_res_panel = res::resources.getResAnim("panel");
    Vector2 bsize(TILE_WIDTH, TILE_HEIGHT);

    uint n = 0;
    for(uint r=0; r<3; r++)
        for(uint c=0; c<3; c++)
        {
            spSprite b = new Sprite;
            borders[n++] = b;
            b->setSize(bsize);
            b->setResAnim(p_res_panel, c, r);
            b->setPosition(c * TILE_WIDTH, r * TILE_HEIGHT);
            addChild(b);
        }
    setSize(128.f, 64.f);


    text_field = new TextField;
    text_field->setFont(res::resources.getResFont("stamper"));
    text_field->setAlign(TextStyle::VerticalAlign::VALIGN_MIDDLE, TextStyle::HorizontalAlign::HALIGN_MIDDLE);
    text_field->setColor(Color(Color::Thistle));
    addChild(text_field);

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
    float p = size.x - TILE_WIDTH;
    borders[2]->setX(p);
    borders[5]->setX(p);
    borders[8]->setX(p);

    Vector2 ch_size(size.x - TILE_WIDTH * 2.f, TILE_HEIGHT);

    borders[1]->setSize(ch_size);
    ch_size.y = TILE_HEIGHT;
    borders[7]->setSize(ch_size);

    p = size.y - TILE_HEIGHT;
    borders[6]->setY(p);
    borders[7]->setY(p);
    borders[8]->setY(p);

    ch_size.y = size.y - TILE_HEIGHT * 2.f;
    ch_size.x = TILE_WIDTH;
    borders[3]->setSize(ch_size);
    borders[5]->setSize(ch_size);
    
    ch_size.x = size.x - TILE_WIDTH * 2.f;
    ch_size.y = size.y - TILE_HEIGHT * 2.f;
    borders[4]->setSize(ch_size);
}


void TextPanel::setText(string text)
{
    
}
