#include "MenuButton.h"
#include "PlayState.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "GameObject.h"
#include "GameState.h"
#include "MenuState.h"
#include "TextureManager.h"
#include <iostream>

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual void camera();
	virtual std::string getStateID() const { return s_gameOverID; }
	static GameOverState* Instance() {
		if (s_pInstance == nullptr)
		{
			s_pInstance = new GameOverState();
		}
		return s_pInstance;
	}

	static void s_gameOverToMain();
	static void s_restartPlay();

private:
	GameOverState() {}

	static GameOverState* s_pInstance;
	static const std::string s_gameOverID;

};