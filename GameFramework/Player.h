#pragma once
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include "Timer.h"



class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	~Player() {}
	virtual void draw();
	virtual void update();
	virtual void clean();
	void handleInput();
	void Gravity(float gravity);
	void checkCollision();
	void CameraMove();
	void Transparency();
	void GameOver();
	


private:
	int isGrounded;
	bool attack;

	Timer _timer;
	int HP;
};