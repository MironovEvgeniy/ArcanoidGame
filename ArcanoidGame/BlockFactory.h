#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArcanoidGame
{
	class Block;

	class BlockFactory
	{
	protected:
		int createdBreackableBlocksCount = 0;

	public:
		virtual std::shared_ptr<Block> createBlock(const sf::Vector2f& position) = 0;
		virtual ~BlockFactory() = default;
		int GetCreatedBreackableBlocksCount();
		void clearCounter();
	};

	class SmoothBlockFactory final: public BlockFactory
	{
	public:
		std::shared_ptr<Block> createBlock(const sf::Vector2f& position) override;
		~SmoothBlockFactory() override = default;
	};

	class UnbreackableBlockFactory final : public BlockFactory
	{
	public:
		std::shared_ptr<Block> createBlock(const sf::Vector2f& position) override;
		~UnbreackableBlockFactory() override = default;
	};

	class StrongBlockFactory final : public BlockFactory
	{
	public:
		std::shared_ptr<Block> createBlock(const sf::Vector2f& position) override;
		~StrongBlockFactory() override = default;
	};
}