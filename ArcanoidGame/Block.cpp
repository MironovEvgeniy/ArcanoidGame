#include "Block.h"
#include "Ball.h"
#include "GameSettings.h"


namespace ArcanoidGame
{
	void Block::Init()
	{
		shape.setOrigin({ BLOCK_WIDTH / 2.f, BLOCK_HEIGHT / 2.f });
		shape.setFillColor(sf::Color::Blue);
		shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
		//shape.setPosition({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	}

	void Block::Update(float timeDelta)
	{

	}

	void Block::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	bool Block::CheckCollisionWithBall(const Ball& ball)
	{		
		/*const auto rect = shape.getGlobalBounds();
		const auto ballPos = ball.GetPosition();*/

		/*return GetRect().intersects(ball.GetRect());*/
		const auto rect = shape.getGlobalBounds();
		const auto ballPos = ball.GetPosition();
		const float radius = BALL_SIZE / 2.f;

		// Находим ближайшую точку на прямоугольнике
		float closestX = std::clamp(ballPos.x, rect.left, rect.left + rect.width);
		float closestY = std::clamp(ballPos.y, rect.top, rect.top + rect.height);

		float dx = ballPos.x - closestX;
		float dy = ballPos.y - closestY;

		return dx * dx + dy * dy < radius * radius;
	}
}