#include "First_Bootstrap_ProjApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "InfiniteBackground.h"
#include "Player.h"
#include "PugBullet.h"
#include "PlayerTwo.h"
#include <imgui.h>
#include "BearBullet.h"
#include "Enemy.h"
#include <iostream>
#include <time.h>

using std::cout;
using std::endl;

First_Bootstrap_ProjApp::First_Bootstrap_ProjApp() {

}

First_Bootstrap_ProjApp::~First_Bootstrap_ProjApp() {

}

bool First_Bootstrap_ProjApp::startup() {

	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	//background
	m_background = new InfiniteBackground();
	m_sprite = new Player(new glm::vec2(105, 300));
	m_spriteTwo = new PlayerTwo(new glm::vec2(105, 650));

	//ENEMY//
	m_enemy = new EnemyObj[e_amount];

		//ENEMY//
	for (int i = 0; i < e_amount; i++)
	{
		m_enemy[i].hasSpawned = false;
		m_enemy[i].fgtEnemy = new Enemy();
	}
	

	//menu gui
    gui_controls = false; 
	gui_IsPlaying = false;
	gui_gameOver = false;


	aie::Texture* frame1 = new aie::Texture("../bin/textures/jetPackPug.png");
	
	aie::Texture* frame11 = new aie::Texture("../bin/textures/jetPackBearV2.png");
	


	m_sprite->AddFrame(frame1, 0.08f);
	
	m_spriteTwo->AddFrame(frame11, 0.15f);
	

	return true;
 }

void First_Bootstrap_ProjApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	//background 
	delete m_background;
	delete m_sprite;
	delete m_spriteTwo;
	delete m_enemy;
}

void First_Bootstrap_ProjApp::update(float deltaTime) {
	srand(time(nullptr));
	// input example
	aie::Input* input = aie::Input::getInstance();
	//background

	m_background->Update(deltaTime);
	
	if (gui_IsPlaying)
	{
		m_spriteTwo->Update(deltaTime, input);
		m_sprite->Update(deltaTime, input);

		//ENEMY//
		for (int i = 0; i < e_amount; i++)
		{
			if (m_enemy[i].hasSpawned == false)
			{
				//m_enemy[i].fgtEnemy->SetTimer(m_enemy[i].fgtEnemy->GetTimer() - (100.0f * deltaTime));
				m_enemy[i].fgtEnemy->SetTimer(m_enemy[i].fgtEnemy->GetTimer() + deltaTime);
				if (m_enemy[i].fgtEnemy->GetTimer() >= 2.0f)
				{
					m_enemy[i].hasSpawned = true;
					m_enemy[i].fgtEnemy->SetPosY(rand() % getWindowHeight()/*(0.0f + (rand() % (1000 - 0 + 1)))*/);
					m_enemy[i].fgtEnemy->SetPosX(2000.0f);
					m_enemy[i].fgtEnemy->SetTimer(0);
				}
			}

			if (m_enemy[i].hasSpawned == true && m_enemy[i].fgtEnemy->GetPosX() < 0)
			{
				m_enemy[i].fgtEnemy->SetPosX(2000.0f);
				m_enemy[i].hasSpawned = false;
			}
		}

		for (int i = 0; i < e_amount; i++)
		{
			m_enemy[i].fgtEnemy->Update(deltaTime);
		}

		// collide
		for (int i = 0; i < e_amount; i++)
		{
			if (m_enemy[i].hasSpawned == true)
			{
				int collide = m_sprite->HitEnemy(m_enemy[i].fgtEnemy->GetPosX(), m_enemy[i].fgtEnemy->GetPosY());

				if (collide != -1)
				{
					--p1_ammo;
					m_sprite->ClearKnife(collide);
					m_enemy[i].fgtEnemy->SetTimer(1920.0f);
					m_enemy[i].fgtEnemy->SetPosY((0.0f + (rand() % (1000 - 0 + 1))));
					m_enemy[i].fgtEnemy->SetPosX(2500.f);
					p1_score += 1000;

				}

				if (((m_enemy[i].fgtEnemy->GetPosX() + 40) >= m_sprite->GetPos()->x) && ((m_enemy[i].fgtEnemy->GetPosX() - 40) <= m_sprite->GetPos()->x))
				{
					if (((m_enemy[i].fgtEnemy->GetPosY() + 40) >= m_sprite->GetPos()->y) && ((m_enemy[i].fgtEnemy->GetPosY() - 40) <= m_sprite->GetPos()->y))
					{
						quit();
					}
				}
			}
			else
			{
				break;
			}
		}

		//bear collide
		for (int i = 0; i < e_amount; i++)
		{
			if (m_enemy[i].hasSpawned == true)
			{
				int collideBear = m_spriteTwo->HitEnemy(m_enemy[i].fgtEnemy->GetPosX(), m_enemy[i].fgtEnemy->GetPosY());

				if (collideBear != -1)
				{
					--p2_ammo;
					m_spriteTwo->ClearBullet(collideBear);
					m_enemy[i].fgtEnemy->SetTimer(1920.0f);
					m_enemy[i].fgtEnemy->SetPosY((0.0f + (rand() % (1000 - 0 + 1))));
					m_enemy[i].fgtEnemy->SetPosX(2500.f);
					p2_score += 1000;

				}

				if (((m_enemy[i].fgtEnemy->GetPosX() + 40) >= m_sprite->GetPos()->x) && ((m_enemy[i].fgtEnemy->GetPosX() - 40) <= m_spriteTwo->GetPos()->x))
				{
					if (((m_enemy[i].fgtEnemy->GetPosY() + 40) >= m_spriteTwo->GetPos()->y) && ((m_enemy[i].fgtEnemy->GetPosY() - 40) <= m_spriteTwo->GetPos()->y))
					{
						quit();
					}
				}
			}
			else
			{
				break;
			}
		}


		if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		{
			quit();
		}
	}
}

void First_Bootstrap_ProjApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	if (!gui_IsPlaying)
	{
		ImGui::Begin("Main Menu: ");
		ImGui::Text("Space Battle!");
		ImGui::Text("*Co-op intended*");
		ImGui::Text("You must destroy the Flame Balls that are approaching your position!");
		ImGui::Text("Destroy as many as you can to reach a high score");

		ImGui::Checkbox("Controls", &gui_controls);

		if (gui_controls)
		{
			ImGui::Begin("Controls: ");

			ImGui::Text("Pug:");
			ImGui::Text("W: fly up");
			ImGui::Text("A: fly left");
			ImGui::Text("S: fly down");
			ImGui::Text("d: fly right");
			ImGui::Text("SPACE: shoot");
			ImGui::Text("");
			ImGui::Text("Bear:");
			ImGui::Text("ARROW UP: fly up");
			ImGui::Text("ARROW LEFT: fly left");
			ImGui::Text("ARROW DOWN: fly down");
			ImGui::Text("ARROW RIGHT: fly right");
			ImGui::Text("CONTROL: shoot");

			if (ImGui::Button("close"))
			{
				gui_controls = false;
			}
			ImGui::End();
		}

		if (ImGui::Button("Start Game"))
		{
			gui_IsPlaying = true;
		}
		ImGui::End();
	}
	

	if (gui_IsPlaying)
	{
		ImGui::Begin("Score Board: ");
		ImGui::Text("Pug Score: %d", p1_score);
		ImGui::Text("Bear Score: %d", p2_score);
		ImGui::End();

	}

	if (gui_IsPlaying)
	{
		ImGui::Begin("");
		ImGui::Text("Pug ammo: %d", p1_ammo);
		ImGui::Text("Bear ammo: %d", p2_ammo);
		ImGui::End();
	}

	m_background->Draw(m_2dRenderer);
	m_sprite->Draw(m_2dRenderer, m_sprite->GetPos());
	m_spriteTwo->DrawNow(m_2dRenderer, m_spriteTwo->GetPos());

	//ENEMY//
	if (gui_IsPlaying)
	{
		int randtime = 0 + (rand() % (300 - 0 + 1));
		for (int i = 0; i < e_amount; i++)
		{
			if (m_enemy[i].hasSpawned == true)
			{
				m_enemy[i].fgtEnemy->Draw(m_2dRenderer);
			}
			else if (((randtime % 300) == 0) && (m_enemy[i].hasSpawned == false))
			{
				m_enemy->hasSpawned = true;
				cout << randtime;
				break;
			}
			else
			{
				break;
			}
		}
	}


	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}