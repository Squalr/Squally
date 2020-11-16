#pragma once
#include <vector>

#include "Engine/UI/HUD/Hud.h"

class MatrixStrand;

class MatrixRain : public Hud
{
public:
	static MatrixRain* create();

protected:
	MatrixRain();
	virtual ~MatrixRain();

private:
	typedef Hud super;
	void pause(void) override;

	std::vector<MatrixStrand*> strands;

	static const int strandCount;
};
