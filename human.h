#pragma once
#include "olcPixelGameEngine.h"
#include <random>
#include <chrono>
#include "globals.h"


enum Place {
	HOME, SHOP
};

class human{
public:
	human() {}
	human(olc::vf2d p) {
		pos = p;
		home = p;
	}
	human(float x, float y) {
		pos = { x, y };
	}
	bool infected = false;
	olc::vf2d pos;
	olc::vf2d vec = {0, 0};
	olc::vf2d target;
	olc::vf2d home;
	std::chrono::high_resolution_clock::time_point timeInfected;
	bool masked = false;
	Place place = HOME;
	static constexpr float speed = 100;
	void updatePos(float elapsedTime) {
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-0.1, 0.1);
		std::uniform_real_distribution<> dis2(0, 0.4);
		if (place == HOME) {
			target =  (home - pos) / std::max(Screenwidth, Screenheight);
		}
		else {
			target = (shop - pos) / std::max(Screenwidth, Screenheight);
		}
		float x = (float)dis(gen);
		float y = (float)dis(gen);
		vec += {x, y};
		vec += target * (float)dis2(gen);
		if (vec.x > 1) vec.x = 1;
		if (vec.y > 1) vec.y = 1;
		if (vec.x < -1) vec.x = -1;
		if (vec.y < -1) vec.y = -1;


		pos += vec * elapsedTime * speed;
		std::uniform_real_distribution<> dis3(-1, 1);
		if (pos.x > Screenwidth) {
			pos = { Screenheight, pos.y };
			vec = { -abs((float)dis3(gen)), (float)dis3(gen) }; // makes it go left
		}
		else if (pos.x < 0) {
			pos = { 0, pos.y };
			vec = { abs((float)dis3(gen)), (float)dis3(gen) }; // makes if go right
		}
		if (pos.y > Screenheight) {
			pos = { pos.x, Screenheight };
			vec = { (float)dis3(gen), -abs((float)dis3(gen)) }; // makes it go up
		}
		else if (pos.y < 0) {
			pos = { pos.x, 0 };
			vec = { (float)dis3(gen), abs((float)dis3(gen)) }; // makes it go down
		}
	}
	void randomiseVec() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-1, 1);
	}
};


