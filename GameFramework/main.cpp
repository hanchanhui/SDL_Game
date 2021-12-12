#include "Game.h"
#include <iostream>

/*
UML 사이트 :https://drive.google.com/file/d/1BDWS0Wr9-bJZyJajW_2O-umTZnpp6l-7/view?usp=sharing

글씨부분은 시간이 부족해 만들지 못했습니다.
*/

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
  if (TheGame::Instance()->init("Chapter 1", 300, 300, 800, 900, false))
  {
    Uint32 frameStart, frameTime;
    while(TheGame::Instance()->running())
    {
      frameStart = SDL_GetTicks();
      TheGame::Instance()->handleEvents();
      TheGame::Instance()->update();
      TheGame::Instance()->render();
      frameTime = SDL_GetTicks() - frameStart;
      if (frameTime < DELAY_TIME) {
        SDL_Delay((int)(DELAY_TIME - frameTime));
      }
    }
  }
  else
  {
    std::cout << "game init failure " << SDL_GetError() << std::endl;
    return -1;
  }

  TheInputHandler::Instance()->clean();
  
  return 0;
}