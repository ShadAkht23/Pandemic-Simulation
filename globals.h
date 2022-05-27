#pragma once
#include "olcPixelGameEngine.h"

const float Screenwidth = 600;
const float Screenheight = 600;

const olc::vf2d shop = olc::vf2d(Screenwidth / 2, Screenheight / 2);
const std::vector<olc::vf2d> homePos = {
	olc::vf2d(Screenwidth / 6, Screenheight / 5),
	olc::vf2d(Screenwidth / 6 * 3, Screenheight / 5),
	olc::vf2d(Screenwidth / 6 * 5, Screenheight / 5),
	olc::vf2d(Screenwidth / 6, Screenheight / 5 * 4),
	olc::vf2d(Screenwidth / 6 * 3, Screenheight / 5 * 4),
	olc::vf2d(Screenwidth / 6 * 5, Screenheight / 5 * 4),
};