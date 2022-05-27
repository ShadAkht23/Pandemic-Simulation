#pragma once
#include"human.h"

class home{
	public:
	std::vector<std::shared_ptr<human> > people = std::vector<std::shared_ptr<human> >();
	olc::vf2d pos;
	home(olc::vf2d d) {
		pos = d;
	}
};

