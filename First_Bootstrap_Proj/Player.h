#pragma once
#include <glm\vec2.hpp>
#include "PugBullet.h"
#include "Enemy.h"
#include <vector>
namespace aie 
{
	class Renderer2D;
	class Input;
	class Texture;
};

struct p1_bulletMech
{
	PugBullet * p1_bullet;
	bool onScreen;
};

struct Frame {
	aie::Texture* m_texture;
	float m_delay;
	Frame(aie::Texture* texture, float delay) : m_texture(texture), m_delay(delay) {}
};

class Player
{
public:
	Player();
	Player(glm::vec2* pos);
	~Player();

	void AddFrame(aie::Texture* texture, float delay);
	void Update(float deltaTime, aie::Input* input);
	void Draw(aie::Renderer2D* renderer, glm::vec2* pos);

	int HitEnemy(float targetX, float targetY); 
	void ClearKnife(int hit);

    glm::vec2* GetPos();

private:
	p1_bulletMech* p1_array;
	glm::vec2* p1_pug;
	std::vector<Frame> m_frames;

	int ammo;
	int m_currentFrame;

	float speed;
	float m_timer;

	bool isAnimate;
	bool isAlive;
};