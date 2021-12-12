#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameOverState.h"
#include "GameStateMachine.h"
#include "Camera.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";
MenuState* MenuState::s_pInstance = nullptr;

void MenuState::update()
{
	camera();
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	TheTextureManager::Instance()->draw("Menupan", 215, 230, 400, 400, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
	TheTextureManager::Instance()->TTFdraw("Escape The Phone", 280,150,300,50,TheGame::Instance()->getRenderer());
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}

}
// MenuState Start
bool MenuState::onEnter()
{
	std::cout << "entering MenuState" << std::endl;
	if (!TheTextureManager::Instance()->load("Assets/Play.png","PlayButton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/Exit.png","ExitButton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/Menupan.png", "Menupan", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	m_gameObjects.push_back(new MenuButton(new LoaderParams(335, 400, 50, 54, "PlayButton"), s_menuToPlay));
	m_gameObjects.push_back(new MenuButton(new LoaderParams(455, 400, 50, 54, "ExitButton"), s_exitFromMenu));

	return true;
}
// MenuState end
bool MenuState::onExit()
{
	TheTextureManager::Instance()->clearFromTextureMap("PlayButton");
	TheTextureManager::Instance()->clearFromTextureMap("ExitButton");
	TheTextureManager::Instance()->clearFromTextureMap("Menupan");
	std::cout << "exiting MenuState" << std::endl;
	return true;
}
// PlayState coll
void MenuState::s_menuToPlay()
{
	std::cout << "Play Button Clicked" << std::endl;
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}
// Game Exit
void MenuState::s_exitFromMenu()
{
	std::cout << "Exit Button Clicked" << std::endl;
	TheGame::Instance()->quit();
}
// Game Camera fixation
void MenuState::camera()
{
	TheCamera::Instance()->getCameraRectX(0);
	TheCamera::Instance()->getCameraRectY(0);

}