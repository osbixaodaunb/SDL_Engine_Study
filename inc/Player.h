#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"
#include "SkillManager.h"
#include "Timer.h"
#include "Bullet.h"

#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Enemy;

class Player : public engine::SDLGameObject{
public:
	Player();

	void load(const engine::LoaderParams* pParams);
	void draw();
	void update();
	void clean();
	typedef uint8_t*(*Callback) ();
	uint8_t* pixelColors;

	void setFireRate(int fireRate){
		m_fireRate = fireRate;
	}
private:
	void handleInput();
	SkillManager m_skillManager;
	std::pair<default_inks, default_inks> m_pSkills;
	bool isFirstSkill = true;
	void move();
	void rotateTowards();
	void dash();
	void useSkill();
	bool m_isDashing;
	Uint32 m_dashTime;
	int m_fireRate;
	BulletCreator bulletCreator;

	Enemy* m_boss = NULL;
};

class PlayerCreator : public engine::BaseCreator{
	engine::GameObject* createGameObject() const{
		return new Player();
	}
};

#endif
