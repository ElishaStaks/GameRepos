#pragma once
#include <glm\vec2.hpp>
#include <vector>
#include "BearBullet.h"

//PLAYER TWO HOLDS THE SAME FUNCTIONS AS PLAYER ONE 

namespace aie
{
	class Renderer2D;
	class Input;
	class Texture;
};


struct p2_bulletMech
{
	BearBullet * p2_bullet;
	bool onScreen;
};


struct FrameTwo 
{
	aie::Texture* m_textureTwo;
	float m_delay;
	FrameTwo(aie::Texture* texture, float delay) : m_textureTwo(texture), m_delay(delay) {}
};

class PlayerTwo
{
public:

	PlayerTwo();
	PlayerTwo(glm::vec2* pos);
	~PlayerTwo();

	void AddFrame(aie::Texture* texture, float delay);
	void Update(float deltaTime, aie::Input* input);
	void DrawNow(aie::Renderer2D* renderer, glm::vec2* pos);

	int HitEnemy(float targetX, float targetY);
	void ClearBullet(int hit);

	glm::vec2* GetPos();

private:
	glm::vec2* p2_bear;
	std::vector<FrameTwo> m_frames;
	p2_bulletMech* b_fireBullet;

	int ammo;
	int m_currentFrame;

	float speed;
	float m_timer;

	bool isAnimating;
};