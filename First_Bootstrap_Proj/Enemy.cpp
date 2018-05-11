#include "Enemy.h"
#include <Renderer2D.h>
#include <Texture.h>



Enemy::Enemy()
{
	e_texture = new aie::Texture("../bin/textures/flameBallV2.png");
}


Enemy::~Enemy()
{
	e_texture = nullptr;
	delete e_texture;
}

void Enemy::Draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(e_texture, e_posX, e_posY, 100.0f, 100.0f);
}

void Enemy::Update(float deltaTime)
{
	e_posX -= 400.0f * deltaTime;
}

void Enemy::SetTimer(float newTimer)
{
	timer = newTimer;
}

float Enemy::GetTimer()
{
	return timer;
}

float Enemy::GetPosX()
{
	return e_posX;
}

void Enemy::SetPosX(float newPosX)
{
	e_posX = newPosX;
}

float Enemy::GetPosY()
{
	return e_posY;
}

void Enemy::SetPosY(float newPosY)
{
	e_posY = newPosY;
}
