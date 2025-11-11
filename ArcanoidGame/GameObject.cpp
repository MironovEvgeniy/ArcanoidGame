#include "GameObject.h"
#include "Sprite.h"

namespace SnakeGame
{
	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
}