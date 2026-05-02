#include <chrono>
#include <iostream>
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
   srand(time(NULL));
   std::chrono::microseconds duration(16667);
   bool game = true;
   bool gameComplete = false;
   bool roundComplete = false;
   auto start_time = std::chrono::steady_clock::now();
   auto current_time = std::chrono::steady_clock::now();
   int playerScore = 0;
   int aiScore = 0;
   while(game) {
      if(gameComplete) {
         sprite[6].setDisplay(true);
         sprite[7].display(true);
         if(aiScore == 10)
            sprite[6].setImageIndex(13);
         else if(playerScore == 10)
            sprite[6].setImageIndex(12);
         if(input == 'y') {
            gameComplete = false;
            roundComplete = false;
            playerScore = 0;
            aiScore = 0;
            sprite[6].setDisplay(false);
            sprite[7].display(false);
            sprite[0].setY(499);
            sprite[1].setY(499);
         }
         else if(input == 'n')
            game = false;
      }
      if(!gameComplete) {
         if(!roundComplete) {
            int startY = 0;
            int startX = rand() % 1;
            if(startX == 0)
               startX *= -1;
            int moveRate = 0;
            int y = 0;
            int moveDirection = 0;
            std::chrono::duration<double> elapsed = current_time - start_time;
            if(elapsed >= duration) { 
               if(input == 'w') {
                  if(moveDirection == 0 || moveDirection == 1) {
                     moveRate = 0;
                     downMove = 2;
                  }
               }
               else if(input == 's') {
                  if(moveDiection == 0 || moveDirection == 2) {
                     moveRate = 0;
                     downMove = 1;
                  }
               }
               if(moveRate < 20)
                  ++moveRate;
               if(input == '\0') {
                  moveRate = 0;
                  moveDirection = 0;
               }
               if(!downMove)
                  y -= moveRate;
               else
                  y = moveRate;
               start_time = std::chrono::steady_clock::now();
               sprite[0].setY(sprite[].getY() + y);
               if(sprite[0].getY() <= 15)
                  sprite[0].setY(16);
               if(sprite[0].getY() >= screenHeight)
                  sprite[0].setY(screenHeight - 1)
               current_time = std::chrono::steady_clock::now();
               elapsed = current_time - start_time;
            }
         }
      }
   }
   return 0;
}
