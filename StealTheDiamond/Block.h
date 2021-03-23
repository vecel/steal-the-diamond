#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
class Block : public Object, public sf::RectangleShape
{
public:
    sf::RectangleShape rect;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

