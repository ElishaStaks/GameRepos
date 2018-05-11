#include "BearBullet.h"
#include <Texture.h>
#include "Input.h"
#include <Renderer2D.h>



BearBullet::BearBullet()
{
	p2_bulletTexture = new aie::Texture("../bin/textures/Bullet_004.png");
}

BearBullet::~BearBullet()
{
	delete p2_bulletTexture;
}

void BearBullet::Draw(aie::Renderer2D * spriteBatch)
{
	spriteBatch->drawSprite(p2_bulletTexture, posx, posy, 100, 70);
}

float BearBullet::GetPosX()
{
	return posx;
}

void BearBullet::SetPosX(float NewPosX)
{
	posx = NewPosX;
}

float BearBullet::GetPosY()
{
	return posy;
}

void BearBullet::SetPosY(float NewPosY)
{
	posy = NewPosY;
}

void BearBullet::Update(float deltaTime)
{
	posx += 200.0f * deltaTime;
}
