#pragma once
#include "Player.h"
#include "Application.h"
#include "Renderer2D.h"
#include "InfiniteBackground.h"
#include "PugBullet.h"
#include "PlayerTwo.h"
#include "BearBullet.h"
#include "Enemy.h"

struct EnemyObj
{
	bool hasSpawned;
	Enemy* fgtEnemy;
};


class First_Bootstrap_ProjApp : public aie::Application {
public:

	First_Bootstrap_ProjApp();
	virtual ~First_Bootstrap_ProjApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	InfiniteBackground* m_background;
	Player*             m_sprite;
	PlayerTwo*          m_spriteTwo;

	//ENEMY//
	EnemyObj*           m_enemy;

	bool gui_controls;
	bool gui_IsPlaying;
	bool gui_gameOver;

	int e_amount = 10;
	int p1_score = 0;
	int p2_score = 0;
	int p1_ammo = 100;
	int p2_ammo = 100;
};