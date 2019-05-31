#pragma once
#include <vector>

#include "Engine/UI/HUD/Hud.h"

class MatrixStrand;

class MatrixRain : public Hud
{
public:
	static MatrixRain* create();

private:
	typedef Hud super;
	MatrixRain();
	~MatrixRain();

	void pause(void) override;

	std::vector<MatrixStrand*> strands;

	static const int strandCount;
};
