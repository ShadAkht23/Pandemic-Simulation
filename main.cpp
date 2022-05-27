#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "human.h"
#include "home.h"
#include "globals.h"
#include <cmath>
#include <memory>
#include <chrono>

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Mask Simulation";
	}

public:
	bool OnUserCreate() override
	{

		population = std::vector<std::shared_ptr<human> >();
		homes = std::vector<home>();
		for (int i = 0; i < 6; i++) {
			homes.push_back(home(homePos[i]));
		}
		for (home& h : homes) {
			for (int i = 0; i < 5; i++) {
				h.people.push_back(std::make_shared<human>(h.pos));
				population.push_back(h.people[i]);
			}
		}
		homes[4].people[3]->infected = true;
		for (auto& h : homes[2].people) {
			h->masked = true;
		}
		
		//DrawCircle(100, 100, 10, olc::RED);
		return true;
	}
	std::chrono::high_resolution_clock::time_point TimeStart = std::chrono::high_resolution_clock::now();
	float time = 0;
	float shopTime = 0;
	bool inShop = false;
	std::vector<home> homes;
	std::vector<std::shared_ptr<human> > population;
	bool OnUserUpdate(float fElapsedTime) override
	{
		time += fElapsedTime;
		if (time > 1) {
			time = 0;
			cough();
		}
		shopTime += fElapsedTime;
		if (shopTime > 5) {
			
			shopTime = 0;
			inShop = !inShop;
			for (std::shared_ptr<human>& h : population) { // reset
				h->place = HOME;
			}
			if (inShop) {
				for (home& h : homes) {
					h.people[0]->place = SHOP;
				}
				std::cout << "shop\n";
			}
			else {
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> dis(0, homes[0].people.size() - 1);
				/*for (home& h : homes) {
					h.people[dis(gen)]->place = SHOP;
				}*/
				std::cout << "back home\n";
			}
		}
		for (auto& u : population) {
			u->updatePos(fElapsedTime);
		}
		//h.updatePos(fElapsedTime);
		//std::cout << "pos: " << h.pos.x << " " << h.pos.y << std::endl;
		//std::cout << "vec: " << h.vec.x << " " << h.vec.y << std::endl;
		Clear(olc::BLACK);
		//recover();
		for (auto& u : population) {
			Draw(*u);
		}
		DrawHomes();

		return true;
	}
	void Draw(const human& h) {
		if (h.infected) FillCircle(h.pos, 2, olc::RED);
		else if (h.masked) FillCircle(h.pos, 2, olc::BLUE);
		else FillCircle(h.pos, 2, olc::GREEN);
	}
	void DrawHomes() {
		for (const auto h : homes) {
			DrawRect(h.pos.x - 10, h.pos.y - 10, 20, 20, olc::BLUE);
		}
		DrawRect(shop.x - 10, shop.y - 10, 20, 20, olc::YELLOW);
	}
	void recover() {
		for (auto& h : population) {
			if (h->infected) {
				if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - h->timeInfected).count() > 8) {
					h->infected = false;
				}
			}
		}
	}
	
	float coughRadius = 15;
	float maskedRadius = 8;
	void cough() {
		std::cout << "cough\n";
		for (const auto& zombie : population) {
			if (!zombie->infected) continue;

			for (auto& healthy : population) {
				if (healthy->infected) continue;
				// zombie vs healthy
				// check if healthy is in range of zombie
				float distance = pow((healthy->pos.x - zombie->pos.x), 2) + pow((healthy->pos.y - zombie->pos.y), 2);
				float radius;
				if (zombie->masked) radius = maskedRadius;
				else radius = coughRadius;
			
				if (distance < pow(radius, 2)) {
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> dis(1,5 );
					//if (dis(gen))
					if (healthy->masked) {
						if (dis(gen) < 2) { // 1/5 mask
							healthy->infected = true;
							healthy->timeInfected = std::chrono::high_resolution_clock::now();
						}
					}
					else {
						if (dis(gen) < 3) { // 2/5 mask
							healthy->infected = true;
							healthy->timeInfected = std::chrono::high_resolution_clock::now();
						}
					}
					
					// chance of infection now
				}
			}
			
		}
	}
};

int main()
{
	Example demo;
	if (demo.Construct(Screenwidth, Screenheight, 1, 1))
		demo.Start();
	return 0;
}




