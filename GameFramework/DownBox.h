#pragma once
#include "SDLGameObject.h"

class DownBox : public SDLGameObject
{
public:
    DownBox(const LoaderParams* pParams);
	~DownBox() {}
	virtual void draw();
	virtual void update();
	virtual void clean();
	void DownBoxCollision();
	void arr();
	//void arrcheck();

private:
 

};