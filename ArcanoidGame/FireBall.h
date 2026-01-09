#pragma once
#include "GameSettings.h"
#include "ICommand.h"
#include "BonusManager.h"
#include "Ball.h" 


namespace ArcanoidGame
{
   class FireBall : public ICommand
   {
   public:
      FireBall(Ball& ball);
      void Execute(Block& block) override {};
      void Execute(Platform& platform) override {}
      void Execute(Ball& ball) override;

   private:
      Ball& ball_;

   };

}