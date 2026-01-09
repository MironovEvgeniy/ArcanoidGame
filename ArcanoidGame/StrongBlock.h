#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"


namespace ArcanoidGame
{
	class StrongBlock : public SmoothDestroyableBlock
	{
	public:
		StrongBlock(const sf::Vector2f& position, sf::Color color = sf::Color::Magenta);
		~StrongBlock() = default;

	protected:
		void OnHit() override;
		
	};
}