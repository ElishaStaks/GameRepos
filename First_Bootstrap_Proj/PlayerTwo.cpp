#include "PlayerTwo.h"
#include <Texture.h>
#include <Input.h>
#include <Renderer2D.h>
#include <iostream>
#include "BearBullet.h"



PlayerTwo::PlayerTwo()
{
}

PlayerTwo::PlayerTwo(glm::vec2 * pos) : m_currentFrame(0), m_timer(0)
{
	p2_bear = pos;
	ammo = 30;
	b_fireBullet = new p2_bulletMech[ammo];
	speed = 350.0f;

	for (int i = 0; i < ammo; i++)
	{
		b_fireBullet[i].onScreen = false;
		b_fireBullet[i].p2_bullet = new BearBullet();
	}
}


PlayerTwo::~PlayerTwo()
{
	//animation deallocation
	for (FrameTwo f : m_frames) {
		delete f.m_textureTwo;
	}
	delete b_fireBullet;
}

void PlayerTwo::AddFrame(aie::Texture * texture, float delay)
{
	m_frames.push_back(FrameTwo(texture, delay));
}


void PlayerTwo::Update(float deltaTime, aie::Input * input)
{
	static int initialTime;
	static int nextTime;
	++nextTime;

	for (int i = 0; i < ammo; ++i)
	{
		b_fireBullet[i].p2_bullet->Update(deltaTime);
		b_fireBullet[i].p2_bullet->SetPosX(b_fireBullet[i].p2_bullet->GetPosX() + (700 * deltaTime));
	}


	for (int i = 0; i < ammo; i++)
	{
		if (b_fireBullet[i].onScreen == false)
		{

			b_fireBullet[i].p2_bullet->SetPosX(b_fireBullet[i].p2_bullet->GetPosX() + (700 * deltaTime));
			if (b_fireBullet[i].p2_bullet->GetPosX() >= 1080)
			{

				b_fireBullet[i].onScreen = false;
				p2_bulletMech temp;
				temp = b_fireBullet[i];

				for (int j = ammo - 1; j >= 0; j--)
				{
					if (b_fireBullet[i].onScreen == false)
					{
						b_fireBullet[i] = b_fireBullet[j];
						std::cout << "SC" << std::endl;
						b_fireBullet[j] = temp;
						break;
					}

				}
			}
		}
	}


	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		if (GetPos()->x < 3000.0f)
		{
		   p2_bear->x += 500.0f * deltaTime;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		if (GetPos()->x > 0)
		{
		   p2_bear->x -= 500.0f * deltaTime;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		if (GetPos()->y < 1080)
		{
		   p2_bear->y += 500.0f * deltaTime;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		if (GetPos()->y > 0)
		{
		   p2_bear->y -= 500.0f * deltaTime;
		}
	}


	if (input->isKeyDown(aie::INPUT_KEY_RIGHT_CONTROL))
	{
		m_timer += deltaTime;
		isAnimating = true;

		if (m_timer >= m_frames.at(m_currentFrame).m_delay) {
			m_timer -= m_frames.at(m_currentFrame).m_delay;
			m_currentFrame++;
			if (m_currentFrame >= m_frames.size())
			{
				m_currentFrame = 0;
				isAnimating = false;

			}
		}

		if ((initialTime + 10) <= nextTime)
		{
			for (int i = 0; i < ammo; i++)
			{
				if (b_fireBullet[i].onScreen == false)
				{
					b_fireBullet[i].onScreen = true;
					b_fireBullet[i].p2_bullet->SetPosX(p2_bear->x);
					b_fireBullet[i].p2_bullet->SetPosY(p2_bear->y);
					initialTime = nextTime;
					break;
				}
			}
		}

	}
}


void PlayerTwo::DrawNow(aie::Renderer2D * renderer, glm::vec2 * pos)
{
	for (int i = 0; i < ammo; i++)
	{
		if (b_fireBullet[i].onScreen == true)
		{
			b_fireBullet[i].p2_bullet->Draw(renderer);
		}
		else
		{
			break;
		}
	}

	FrameTwo frame = m_frames.at(m_currentFrame);
	renderer->drawSprite(frame.m_textureTwo, pos->x, pos->y, 250.0f, 300.0f);
}

int PlayerTwo::HitEnemy(float targetX, float targetY)
{
	for (int i = 0; i < ammo; i++)
	{
		if (b_fireBullet[i].onScreen == true)
		{
			float distX = targetX - b_fireBullet[i].p2_bullet->GetPosX();
			float distY = targetY - b_fireBullet[i].p2_bullet->GetPosY();
			if (distX < 50 && distX > -50 && distY > -50 && distY < 50)
			{
				return i;
			}
		}
	}
	return -1;
}

void PlayerTwo::ClearBullet(int hit)
{
	b_fireBullet[hit].onScreen = false;
	p2_bulletMech temp;

	temp = b_fireBullet[hit];

	for (int i = ammo - 1; i >= 0; i--)
	{
		if (b_fireBullet[i].onScreen == true)
		{
			b_fireBullet[hit] = b_fireBullet[i];
			b_fireBullet[i] = temp;
			break;
		}
	}
}

glm::vec2 * PlayerTwo::GetPos()
{
	return p2_bear;
}
