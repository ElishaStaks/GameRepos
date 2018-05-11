#include "PugBullet.h"
#include <Texture.h>
#include "Input.h"
#include <Renderer2D.h>



PugBullet::PugBullet()
{
	p1_bulletTexture = new aie::Texture("../bin/textures/Bullet_004.png");
}

PugBullet::~PugBullet()
{
	delete p1_bulletTexture;
}

void PugBullet::Draw(aie::Renderer2D * spriteBatch)
{
	spriteBatch->drawSprite(p1_bulletTexture, posx, posy, 100, 70);
}

float PugBullet::GetPosX()
{
	return posx;
}

void PugBullet::SetPosX(float NewPosX)
{
	posx = NewPosX;
}

float PugBullet::GetPosY()
{
	return posy;
}

void PugBullet::SetPosY(float NewPosY)
{
	posy = NewPosY;
}

void PugBullet::Update(float deltaTime)
{
	posx += 200.0f * deltaTime;
}
