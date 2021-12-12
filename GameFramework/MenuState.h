#pragma once
#include "GameState.h"


class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual void camera();
	virtual std::string getStateID() const { return s_menuID; }

	static MenuState* Instance()
	{
		if (s_pInstance == nullptr) {
			s_pInstance = new MenuState();
		}
		return s_pInstance;
	}

	static void s_menuToPlay();
	static void s_exitFromMenu();
private:
	MenuState() {}

	static MenuState* s_pInstance;
	static const std::string s_menuID;
};