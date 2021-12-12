#pragma once
#ifndef __Game__
#define __Game__

#include "SDL.h"
#include "GameObject.h"
#include <vector>
#include "InputHandler.h"
#include "GameStateMachine.h"


class Game
{
public:
  Game() {}
  static Game* Instance()
  {
    if (s_pInstance == 0) s_pInstance = new Game();
    return s_pInstance;
  }
  ~Game() {}

  bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
  void render();
  void update();
  bool running();
  void handleEvents();
  void clean();
  
  SDL_Renderer* getRenderer() const { return m_pRenderer; }
  
  void quit() { m_bRunning = false; }

  GameStateMachine* getStateMachine()
  {
      return m_pGameStateMachine;
  }
  

private:
  static Game* s_pInstance;
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;
  bool m_bRunning;
  
  GameStateMachine* m_pGameStateMachine;

};
typedef Game TheGame;

#endif