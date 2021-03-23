#include "Block.h"

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->rect, states);
}
