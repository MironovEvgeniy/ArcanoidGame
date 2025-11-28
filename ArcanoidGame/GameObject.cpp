#include "GameObject.h"
#include "Sprite.h"

namespace ArcanoidGame
{
	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
}