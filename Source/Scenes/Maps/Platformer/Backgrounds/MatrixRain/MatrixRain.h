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

	virtual void pause(void) override;
	void onEnter() override;
	void setPositions();

	std::vector<MatrixStrand*> strands;

	static const int strandCount;
};
