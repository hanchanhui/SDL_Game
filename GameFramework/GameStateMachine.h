#pragma once
#include "GameState.h"

class GameStateMachine
{
public:
	//State를 바꿔주는 역할
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();

private:
	GameState* m_currentState;
	GameState* m_prevState;
};