#include "base.h"



Vector2 _get_absolute_pos(const Actor *p_actor, float x, float y)
{
    const Actor *p_parent_actor = p_actor->getParent();

    if(p_parent_actor == nullptr)
        return Vector2(x, y);

    x -= p_parent_actor->getX();
    y -= p_parent_actor->getY();
    return _get_absolute_pos(p_parent_actor, x, y);
}


Vector2 getAbsolutePosition(const Actor *p_actor)
{
    return _get_absolute_pos(p_actor, p_actor->getX(), p_actor->getY());
}
