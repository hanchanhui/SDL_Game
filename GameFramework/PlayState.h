#pragma once
#include "GameState.h"
#include "SDLGameObject.h"
#include <vector>
#include "Timer.h"
#include <SDL_mixer.h>

#define ARR1 17
#define ARR2 10

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	void Random();
	void RandomVal();
	void GamesEnding();

	virtual std::string getStateID() const { return s_playID; }
	virtual ~PlayState();

	static PlayState* Instance()
	{
		if (s_pInstance == nullptr) {
			s_pInstance = new PlayState();
		}
		return s_pInstance;
	}

	std::vector<GameObject*> getWall() const { return m_wall; }
	std::vector<GameObject*> getPlayer() const { return m_gameObjects; }
	std::vector<GameObject*> getDownBox() const { return m_downBox; }
	std::vector<GameObject*> getHeart() const { return m_heart; }
	void SetAniCount(int a) { AniCount = a; }
	void SetHeartAni(int a, int b) { heartAni[a] = b; }
	int getHeartAni(int a) { return heartAni[a]; }


	void setMap(int a, int b, int c) { map[a][b] = c; }
	int getMap(int a, int b) { return map[a][b]; }
	bool getGameBoxStop() { return GameBoxStop; }


private:
	PlayState();

	static PlayState* s_pInstance;
	static const std::string s_playID;

	std::vector<GameObject*> m_wall;
	std::vector<GameObject*> m_downBox;
	std::vector<GameObject*> m_heart;

	Timer _timer;
	Mix_Music* _bgm;

	int** map;

	int AniCount;
	int heartAni[3];
	int random;
	int randomValue;
	bool GameBoxStop;
	bool GameEnding;
	int ReRandom;
};
