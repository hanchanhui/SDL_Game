#pragma once

#include "SDL.h"
#include <string>
#include <map>
#include <SDL_ttf.h>





class TextureManager
{
public:
  static TextureManager* Instance()
  {
    if (s_pInstance == 0) s_pInstance = new TextureManager();
    return s_pInstance;
  }
  ~TextureManager() {}

  bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

  void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip);

  void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip);

  int TTFdraw(const char* id, int x, int y, int width, int height, SDL_Renderer* pRenderer);

  void clearFromTextureMap(std::string id)
  {
	  m_textureMap.erase(id);
  }

 
  bool getPlayerColCheck() { return PlayerColCheck; }
  void setPlayerColCheck(bool a) { PlayerColCheck = a; }


private:
  TextureManager() : mTexture(NULL), PlayerColCheck(false) { }
  static TextureManager* s_pInstance;
  std::map<std::string, SDL_Texture*> m_textureMap;

  SDL_Texture* mTexture;
  bool PlayerColCheck;
  
};
typedef TextureManager TheTextureManager;