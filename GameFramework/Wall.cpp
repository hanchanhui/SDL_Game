#include "Wall.h"

Wall::Wall(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Wall::draw()
{
  SDLGameObject::draw();
  SDLGameObject::flip = SDL_FLIP_NONE;
}

void Wall::update()
{
  
}

void Wall::clean()
{
  
}