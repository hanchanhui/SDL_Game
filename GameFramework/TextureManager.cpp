#include "TextureManager.h"
#include "SDL_image.h"
#include "Camera.h"


TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
  if (pTempSurface == 0) return false;

  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
  SDL_FreeSurface(pTempSurface);
  if (pTexture != 0)
  {
    m_textureMap[id] = pTexture;
    return true;
  }

  return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x - TheCamera::Instance()->getCameraRect().x;
  destRect.y = y - TheCamera::Instance()->getCameraRect().y;

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = width * currentFrame;
  srcRect.y = height * currentRow;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x - TheCamera::Instance()->getCameraRect().x;
  destRect.y = y - TheCamera::Instance()->getCameraRect().y;

  // 무적 상태
  if (PlayerColCheck == true)
  {
      SDL_SetTextureAlphaMod(m_textureMap[id], 100);
  }
  else if (PlayerColCheck == false)
  {
      SDL_SetTextureAlphaMod(m_textureMap[id], 255);
  }

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

int TextureManager::TTFdraw(const char* id, int x, int y, int width, int height, SDL_Renderer* pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    if (TTF_Init() < 0) { printf("오류: 폰트를 초기화할 수 없습니다. (%s)\n", TTF_GetError()); return false; }
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\comicbd.ttf", 32);
    if (font == NULL)
    {
        printf("Could not open font! (%s)\n", TTF_GetError());
        return -1;
    }

    SDL_Color color = { 0, 0, 0, SDL_ALPHA_OPAQUE };
    SDL_Surface* surface = TTF_RenderText_Blended(font, id, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);

    SDL_FreeSurface(surface);

    SDL_RenderCopy(pRenderer, texture, &srcRect, &destRect);

}
