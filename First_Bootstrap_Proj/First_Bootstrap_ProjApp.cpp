#include "First_Bootstrap_ProjApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "InfiniteBackground.h"
#include "Player.h"
#include "PugBullet.h"
#include "PlayerTwo.h"
//for the main menu 
#include <imgui.h>
#include "BearBullet.h"
#include "Enemy.h"
#include <iostream>
//for rand time
#include <time.h>

//namesaces to print out to the console
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

	//creates a new background 
	m_background = new InfiniteBackground();
	//takes the player sprite and creates a new player sprite and sets the position of it
	m_sprite = new Player(new glm::vec2(105, 300));
	//takes the second player and dynamically allocates it and gives it a position
	m_spriteTwo = new PlayerTwo(new glm::vec2(105, 650));

	//dynamically allocating the enemy with a new struct which takes in the amount of enemies i want to randomise
	m_enemy = new EnemyObj[e_amount];

	//cycles through the amount of enemies
	for (int i = 0; i < e_amount; i++)
	{
		//then it takes the enemies and sets it to false which means it hasnt spawned
		m_enemy[i].hasSpawned = false;
		//then it takes thoughs enemies and creates new enemies using the struct we made in the app.h
		m_enemy[i].fgtEnemy = new Enemy();
	}
	
	//menu gui
    gui_controls = false; 
	gui_IsPlaying = false;
	gui_gameOver = false;

	//creates a texture of frame 1 and find the texture in the folders
	//this is player one sprite 
	aie::Texture* frame1 = new aie::Texture("../bin/textures/jetPackPug.png");
	//creates a texture of frame 11 and find the texture in the folders
	//this is player two sprite
	aie::Texture* frame11 = new aie::Texture("../bin/textures/jetPackBearV2.png");
	
	//takes player one sprite and points to the add frame function and then takes frame 1 sprite and moves the animation at that speed
	m_sprite->AddFrame(frame1, 0.08f);
	//takes player two sprite and points to the add frame function and then takes frame 1 sprite and moves animation at that speed
	m_spriteTwo->AddFrame(frame11, 0.15f);
	
	return true;
 }

void First_Bootstrap_ProjApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	//deletes the background texture
	delete m_background;
	//delets the player one texture 
	delete m_sprite;
	//deletes the player two texture
	delete m_spriteTwo;
	//deletes the enemy texture
	delete m_enemy;
}

void First_Bootstrap_ProjApp::update(float deltaTime) {
	//creates a seed for the rand 
	srand(time(nullptr));
	// input example
	aie::Input* input = aie::Input::getInstance();
	//background
	//gets the background and points to the update function which then allows it to update every frame using the function above
	m_background->Update(deltaTime);

	//checks if the game is playing
	//if it is it will run everything below
	if (gui_IsPlaying)
	{
		//updates the player two sprite 
		m_spriteTwo->Update(deltaTime, input);
		//updates the player one sprite
		m_sprite->Update(deltaTime, input);

		//enemy spawning code
		//a for loop which cycles through the amount of enemies and increments it
		for (int i = 0; i < e_amount; i++)
		{
			//sets the enemies to not spawning 
			if (m_enemy[i].hasSpawned == false)
			{
				//if thats true then get the enemies and sets the timer and updates it by the delta time aka update function
				m_enemy[i].fgtEnemy->SetTimer(m_enemy[i].fgtEnemy->GetTimer() + deltaTime);
				//this checks if the game has started after 2 seconds the enemies will start spawning in and it will get the timer
				if (m_enemy[i].fgtEnemy->GetTimer() >= 2.0f)
				{
					//if thats true then the enemies have spawned
					m_enemy[i].hasSpawned = true;
					//the enemies spawn in a random y position of the screen height
					m_enemy[i].fgtEnemy->SetPosY(rand() % getWindowHeight());
					//gets the enemies x position and sets it to spawn at 2000 which is off the screen on the right
					m_enemy[i].fgtEnemy->SetPosX(2000.0f);
					//takes the enemies and sets the timer to 0 
					m_enemy[i].fgtEnemy->SetTimer(0);
				}
			}

			//if the enemies have spawned and the enemies x position is lower than 0 
			if (m_enemy[i].hasSpawned == true && m_enemy[i].fgtEnemy->GetPosX() < 0)
			{
				//then they will de spawn at x position of 2000 off the other side of the screen
				m_enemy[i].fgtEnemy->SetPosX(2000.0f);
				//enmies spawn will eual false meaning they will disappear
				m_enemy[i].hasSpawned = false;
			}
		}
		//takes the enmies and cycles through them 
		for (int i = 0; i < e_amount; i++)
		{
			//updates the position 
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