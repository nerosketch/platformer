/* 
 * File:   base.h
 * Author: ns
 *
 * Created on October 21, 2018, 8:33 AM
 */

#ifndef BASE_H
#define BASE_H

#include <stdlib.h>
#include <string>


using namespace std;


class Base
{
/*public:
    Base();
    Base(const Base& o);
    virtual ~Base();*/
};

#define RANDOM_RANGE(min, max)  (rand()%(max-min+1) + min)


class GameError{
public:
    GameError():
    error_code(0),
    error_text(){}

    GameError(unsigned int code, string text):
    error_code(code),
    error_text(text){}

    inline bool operator == (const uint& dig)
    {
        return error_code==dig;
    }
    inline bool operator == (const string& text)
    {
        return error_text==text;
    }
    inline bool operator !=(const uint& dig)
    {
        return error_code!=dig;
    }
    inline bool operator != (const string& text)
    {
        return error_text!=text;
    }

    friend ostream& operator << (ostream &s, const GameError &v)
    {
        if(v.error_text.empty())
            return s;
        s << v.error_text;
        return s;
    }

    unsigned int error_code;
    string error_text;
};


#endif /* BASE_H */

