#pragma once

#include "SDL.h"
#include "Vector2D.h"
#include <vector>

enum mouse_buttons {
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};

class InputHandler {
  public:
    ~InputHandler() {}
    static InputHandler* Instance() 
    {
      if(s_pInstance == 0) 
      {
        s_pInstance = new InputHandler();
      }
      return s_pInstance;
    }
    bool isKeyDown(SDL_Scancode key);
    void update();
    void clean() {}
    bool getMouseButtonState(int buttonNumber);
    void onMouseMove(SDL_Event event);
    void onMouseButtonDown(SDL_Event event);
    void onMouseButtonUp(SDL_Event event);
    void onKeyDown();
    void onKeyUp();
    
    Vector2D* getMousePosition();

  private:
    InputHandler();
    static InputHandler* s_pInstance;
    const Uint8* m_keystates;
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
};

typedef InputHandler TheInputHandler;
