#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "DownBox.h"
#include "Player.h"
#include "Wall.h"
#include "heart.h"
#include <cstdlib>
#include <iostream>


const std::string PlayState::s_playID = "PLAY";
PlayState* PlayState::s_pInstance = nullptr;

// new two-dimensional array and variable init
PlayState::PlayState() : AniCount(0), random(0), randomValue(10), GameBoxStop(false), GameEnding(false), ReRandom(0)
{
	map = new int* [ARR1];
	for (int i = 0; i < ARR1; i++)
	{
		map[i] = new int[ARR1];
	}
	for (int i = 0; i < ARR1; i++)
	{
		for (int j = 0; j < ARR2; j++)
		{
			map[i][j] = NULL;
		}
	}

	_timer.setInterval(1000);
	heartAni[0] = 0;
	heartAni[1] = 2;
	heartAni[2] = 4;
}

// two-dimensional array delete
PlayState::~PlayState()
{
	for (int i = 0; i < ARR1; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

// PlayState Start
bool PlayState::onEnter()
{
	//Sound
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	_bgm = Mix_LoadMUS("Assets/_bgm.mp3");
	Mix_VolumeMusic(3);
	Mix_PlayMusic(_bgm, -1);
	//load
	std::cout << "entering PlayState" << std::endl;
	if (!TheTextureManager::Instance()->load("Assets/Player.png", "Player", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/PlayerRun.png", "PlayerRun", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/TmGround.png", "TmGround", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/MdGround.png", "MdGround", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/box.png", "box", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/DownBox.png", "Downbox", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/heart.png", "heart", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/heart_white.png", "heart_white", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	m_gameObjects.push_back(new Player(new LoaderParams(580, 700, 64, 64, "Player")));
	m_gameObjects.push_back(new Player(new LoaderParams(580, 700, 64, 64, "PlayerRun")));

	for (int i = 360; i < 840; i += 24)
	{
		m_wall.push_back(new Wall(new LoaderParams(i, 910, 24, 24, "box")));
	}
	m_wall.push_back(new Wall(new LoaderParams(852, 190, 32, 32, "box")));
	m_wall.push_back(new Wall(new LoaderParams(884, 190, 32, 32, "box")));
	m_wall.push_back(new Wall(new LoaderParams(916, 190, 32, 32, "box")));
	

	m_heart.push_back(new heart(new LoaderParams(500, 5, 64, 64, "heart")));
	m_heart.push_back(new heart(new LoaderParams(500, 5, 64, 64, "heart_white")));
	m_heart.push_back(new heart(new LoaderParams(580, 5, 64, 64, "heart")));
	m_heart.push_back(new heart(new LoaderParams(580, 5, 64, 64, "heart_white")));
	m_heart.push_back(new heart(new LoaderParams(660, 5, 64, 64, "heart")));
	m_heart.push_back(new heart(new LoaderParams(660, 5, 64, 64, "heart_white")));

	_timer.start();

	return true;
}

void PlayState::render()
{
	TheTextureManager::Instance()->draw("MdGround", 350, 90, 500, 860, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
	m_gameObjects[AniCount]->draw();
	m_heart[heartAni[0]]->draw();
	m_heart[heartAni[1]]->draw();
	m_heart[heartAni[2]]->draw();

	for (int i = 0; i < m_wall.size(); i++)
	{
		m_wall[i]->draw();
	}

	for (int i = 0; i < m_downBox.size(); i++)
	{
		m_downBox[i]->draw();
	}

	TheTextureManager::Instance()->draw("TmGround", 0, 0, 1200, 1000, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
}

void PlayState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	for (int i = 0; i < m_wall.size(); i++)
	{
		m_wall[i]->update();
	}

	for (int i = 0; i < m_downBox.size(); i++)
	{
		m_downBox[i]->update();
	}

	for (int i = 0; i < m_heart.size(); i++)
	{
		m_heart[i]->update();
	}

	if (!GameBoxStop)
	{
		Random();
		RandomVal();
	}
	else if (GameBoxStop)
	{
		m_downBox.push_back(new Wall(new LoaderParams(820, 190, 32, 32, "box")));
	}
	GamesEnding();
	
}

// Down blocks
void PlayState::Random()
{
	srand((unsigned int)time(NULL));
	random = 360 + (48 * (rand() % randomValue));
	
	
	if (!GameBoxStop && _timer.done() && (ReRandom != random))
	{
		m_downBox.push_back(new DownBox(new LoaderParams(random, 0, 48, 48, "Downbox")));
		_timer.pause();
		ReRandom = random;
	}

	if (_timer.getstart() != 0)
	{
		_timer.resume();
	}
}
// Set the difficulty level of difficulty
void PlayState::RandomVal()
{
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 10; j++) {
			
			if (map[1][j] == 1)
			{
				GameBoxStop = true;
			}
			else if (map[4][j + 5] == 1 && j < 4)
			{
				randomValue = j + 5;
			}

			if (map[6][j] == 1)
			{
				_timer.setInterval(900);
			}
			else if (map[10][j] == 1)
			{
				_timer.setInterval(400);
			}
			else if (map[14][j] == 1)
			{
				_timer.setInterval(600);
			}
		}
	}
}
// Game Ending
void PlayState::GamesEnding()
{
	if (GameBoxStop)
	{
		std::cout << "µé¾î¿È" << std::endl;
		_timer.setInterval(5000);
		
		if (_timer.done())
		{
			std::cout << "ÀÛµ¿" << std::endl;
			for (int i = 0; i < m_wall.size(); i++) {
				m_wall[i]->clean();
			}
			m_wall.clear();
		}
	}
}
// playState end
bool PlayState::onExit()
{
	std::cout << "exiting PlayState" << std::endl;
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	for (int i = 0; i < m_wall.size(); i++) {
		m_wall[i]->clean();
	}
	for (int i = 0; i < m_downBox.size(); i++) {
		m_downBox[i]->clean();
	}
	m_gameObjects.clear();
	m_wall.clear();
	m_downBox.clear();
	
	Mix_FreeMusic(_bgm);

	return true;
}

