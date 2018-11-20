/* 
 * File:   TextPanel.cpp
 * Author: ns
 * 
 * Created on October 21, 2018, 8:44 AM
 */

#include "flags.h"
#include "resources.h"
#include "TextPanel.h"


TextPanel::TextPanel(const string text): border_size(16.f, 16.f)
{
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
    //setSize(128.f, 64.f);


    text_field = new TextField;
    text_field->setFont(res::resources.getResFont("stamper"));
    //text_field->setAlign(TextStyle::VerticalAlign::VALIGN_TOP, TextStyle::HorizontalAlign::HALIGN_LEFT);
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
    // Положение правой стороны
    float p = size.x - TILE_WIDTH + border_size.x;
    borders[2]->setX(p);
    borders[5]->setX(p);
    borders[8]->setX(p);

    // Положение левой стороны
    if(border_size.x > 0.f)
    {
        borders[0]->setX(-border_size.x);
        borders[3]->setX(-border_size.x);
        borders[6]->setX(-border_size.x);
    }

    // Ширина верхнего и нижнего ребра
    Vector2 ch_size(size.x, TILE_HEIGHT);
    borders[1]->setX(0.f);
    borders[1]->setSize(ch_size);
    borders[7]->setX(0.f);
    borders[7]->setSize(ch_size);

    // Позиция нижней стороны
    p = size.y - TILE_HEIGHT + border_size.y;
    borders[6]->setY(p);
    borders[7]->setY(p);
    borders[8]->setY(p);
    
    // позиция верхней стороны
    if(border_size.y > 0.f)
    {
        borders[0]->setY(-border_size.y);
        borders[1]->setY(-border_size.y);
        borders[2]->setY(-border_size.y);
    }

    // Высота левой и правой стороны
    ch_size.y = size.y;
    ch_size.x = TILE_WIDTH;
    borders[3]->setSize(ch_size);
    borders[3]->setY(0.f);
    borders[5]->setSize(ch_size);
    borders[5]->setY(0.f);

    // Размер центрального блока
    //ch_size.x = size.x;
    //ch_size.y = size.y - TILE_HEIGHT * 2.f;
    borders[4]->setPosition(0.f, 0.f);
    borders[4]->setSize(size);
}


void TextPanel::setText(const string& text)
{
    text_field->setText(text);

    RectF b;
    text_field->getBounds(b);
    //const Vector2 &sz = text_field->getSize();

    //setPosition(b.pos);
    setSize(b.size);
}
