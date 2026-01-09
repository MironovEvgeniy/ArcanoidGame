#include "FireBall.h"
#include "GameSettings.h"


namespace ArcanoidGame
{
   FireBall::FireBall(Ball& ball)
      : ball_(ball)
   {
   }

   void FireBall::Execute(Ball& ball)
   {
      if (BonusManager::IsFastBallActive())
      {
         ball_.SetSpeed(SETTINGS.BALL_BONUS_SPEED);
         ball_.SetColor(sf::Color::Red);
      }
      else
      {
         ball_.SetSpeed(SETTINGS.BALL_SPEED);
         ball_.SetColor(sf::Color::Blue);
      }
   }

}