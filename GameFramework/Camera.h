#pragma once
#include <iostream>
#include "SDL.h"


class Camera
{
public:
  static Camera* Instance()
  {
    if (s_pInstance == 0) s_pInstance = new Camera();
    return s_pInstance;
  }


  SDL_Rect getCameraRect() {return cameraRect;}
  void getCameraRectX(int a) {cameraRect.x = a;}
  void getCameraRectY(int b) {cameraRect.y = b;}
  

private:
  Camera() 
  {
    cameraRect.x = 0;
    cameraRect.y = 0;
    cameraRect.w = 640;
    cameraRect.h = 360;
  }
  static Camera* s_pInstance;
  SDL_Rect cameraRect;

};

typedef Camera TheCamera;