#include "Player.h"
#include <Texture.h>
#include "Input.h"
#include <Renderer2D.h>
#include "PugBullet.h"
#include <iostream>
#include "PlayerTwo.h"
#include "First_Bootstrap_ProjApp.h"


Player::Player()
{

}

Player::Player(glm::vec2* pos) : m_currentFrame(0), m_timer(0)
{
	p1_pug = pos;

	ammo = 100;
	p1_array = new p1_bulletMech[ammo];
	speed = 350.0f;

	for (int i = 0; i < ammo; i++)
	{
		p1_array[i].onScreen = false;
		p1_array[i].p1_bullet = new PugBullet();
	}
}


Player::~Player()
{
	//animation deallocation
	for (Frame f : m_frames) {
		delete[] f.m_texture;
	}
	delete p1_array;
}	


void Player::AddFrame(aie::Texture* texture, float delay)
{
	m_frames.push_back(Frame(texture, delay));
}

void Player::Update(float deltaTime, aie::Input* input)
{
	static int initialTime;
	static int nextTime;
	++nextTime;

	for (int i = 0; i < ammo; ++i)
	{
		p1_array[i].p1_bullet->Update(deltaTime);
	    p1_array[i].p1_bullet->SetPosX(p1_array[i].p1_bullet->GetPosX() + (600 * deltaTime));
	}


	for (int i = 0; i < ammo; i++)
	{
		if (p1_array[i].onScreen == false)
		{

			p1_array[i].p1_bullet->SetPosX(p1_array[i].p1_bullet->GetPosX() + (600 * deltaTime));
			if (p1_array[i].p1_bullet->GetPosX() >= 1920)
			{

				p1_array[i].onScreen = false;
				p1_bulletMech temp;
				temp = p1_array[i];

				for (int j = ammo - 1; j >= 0; j--)
				{//kratos was here
					if (p1_array[i].onScreen == false)
					{
						p1_array[i] = p1_array[j];
						std::cout << "SC" << std::endl;
						p1_array[j] = temp;
						break;
					}

				}
			}
		}
	}


	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		if (GetPos()->x < 3000.0f)
		{
		   p1_pug->x += 500.0f * deltaTime;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		if (GetPos()->x > 0)
		{
		   p1_pug->x -= 500.0f * deltaTime;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		if (GetPos()->y < 1080)
		{
		   p1_pug->y += 500.0f * deltaTime;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		if (GetPos()->y > 0)
		{
		   p1_pug->y -= 500.0f * deltaTime;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		m_timer += deltaTime;
		//isAnimate = true;

		//if (m_timer >= m_frames.at(m_currentFrame).m_delay) {
		//	m_timer -= m_frames.at(m_currentFrame).m_delay;
		//	m_currentFrame++;
		//	if (m_currentFrame >= m_frames.size())
		//	{
		//		m_currentFrame = 0;
		//		isAnimate = false;
		//		
		//	}
		//}

		if ((initialTime + 15) <= nextTime)
		{
			for (int i = 0; i < ammo; i++)
			{
				if (p1_array[i].onScreen == false)
				{
					p1_array[i].onScreen = true;
					p1_array[i].p1_bullet->SetPosX(p1_pug->x); 
					p1_array[i].p1_bullet->SetPosY(p1_pug->y);
					initialTime = nextTime;
					break;
				}
			}
		}
	}
}

void Player::Draw(aie::Renderer2D* renderer, glm::vec2* pos)
{
	for (int i = 0; i < ammo; i++)
	{
		if (p1_array[i].onScreen == true)
		{
			p1_array[i].p1_bullet->Draw(renderer);
		}
		else
		{
			break;
		}
	}

	Frame frame = m_frames.at(m_currentFrame);
	renderer->drawSprite(frame.m_texture, pos->x, pos->y , 300.0f, 290.0f);
}

int Player::HitEnemy(float targetX, float targetY)
{
	for (int i = 0; i < ammo; i++)
	{
		if (p1_array[i].onScreen == true)
		{
			float distX = targetX - p1_array[i].p1_bullet->GetPosX();
			float distY = targetY - p1_array[i].p1_bullet->GetPosY();
			if (distX < 50 && distX > -50 && distY > -50 && distY < 50)
			{
				return i;
			}
		}
	}
	return -1;
}

void Player::ClearKnife(int hit)
{
	p1_array[hit].onScreen = false;
	p1_bulletMech temp;

	temp = p1_array[hit];

	for (int i = ammo - 1; i >= 0; i--)
	{
		if (p1_array[i].onScreen == true) 
		{
			p1_array[hit] = p1_array[i];
			p1_array[i] = temp;
			break;
		}
	}
}

glm::vec2 * Player::GetPos()
{
	return p1_pug;
} 