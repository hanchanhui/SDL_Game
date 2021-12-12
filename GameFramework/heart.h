#pragma once
#include <iostream>
#include "SDLGameObject.h"
#include "SDL.h"


class heart : public SDLGameObject
{
public:
    heart(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    


private:
    

};

