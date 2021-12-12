#include "GameOverState.h"
#include "Camera.h"
#include "PlayState.h"

const std::string GameOverState::s_gameOverID = "GAME OVER";
GameOverState* GameOverState::s_pInstance = nullptr;
// MenuState coll
void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
}
// PlayState coll
void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}

void GameOverState::update()
{
	camera();
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	TheTextureManager::Instance()->draw("Menupan", 215, 230, 400, 400, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
	TheTextureManager::Instance()->TTFdraw("Game Over", 280, 150, 300, 70, TheGame::Instance()->getRenderer());
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}
}

// GameOverState Start
bool GameOverState::onEnter()
{
	if (!TheTextureManager::Instance()->load("Assets/Menupan.png", "Menupan", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/Menu.png", "Menu", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/Repeat.png", "repeat", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	
	m_gameObjects.push_back(new MenuButton(new LoaderParams(335, 400, 50, 54, "Menu"), s_gameOverToMain));
	m_gameObjects.push_back(new MenuButton(new LoaderParams(455, 400, 50, 54, "repeat"), s_restartPlay));
	
	PlayState::Instance()->SetHeartAni(0, 0);
	PlayState::Instance()->SetHeartAni(1, 2);
	PlayState::Instance()->SetHeartAni(2, 4);

	std::cout << "Entering PauseSate" << std::endl;
	return true;
}
// GameOverState end
bool GameOverState::onExit()
{
	
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	
	TheTextureManager::Instance()->clearFromTextureMap("Menu");
	TheTextureManager::Instance()->clearFromTextureMap("repeat");
	TheTextureManager::Instance()->clearFromTextureMap("Menupan");
	std::cout << "Exiting PauseState" << std::endl;

	return true;
}
// Game Camera fixation
void GameOverState::camera()
{
	TheCamera::Instance()->getCameraRectX(0);
	TheCamera::Instance()->getCameraRectY(0);
}