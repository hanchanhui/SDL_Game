#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
  SDLGameObject(const LoaderParams* pParams);
  virtual void draw();
  virtual void drawFrame();
  virtual void update();
  virtual void clean();
  virtual ~SDLGameObject() {}

  Vector2D GetPos() { return m_position; }
  Vector2D GetVel() { return m_velocity; }
  Vector2D GetAcc() { return m_acceleration; }
  int GetWidth() {return m_width;}
  int GetHeight() {return m_height;}
  

protected:
  std::string m_textureID;

  int m_x;
  int m_y;
  int m_width;
  int m_height;
  int m_currentRow;
  int m_currentFrame;

  SDL_RendererFlip flip;

  Vector2D m_position;
  Vector2D m_velocity;
  Vector2D m_acceleration;
};
