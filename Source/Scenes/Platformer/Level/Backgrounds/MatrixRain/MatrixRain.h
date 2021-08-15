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
	
	void pause(void) override;

private:
	typedef Hud super;

	std::vector<MatrixStrand*> strands;

	static const int strandCount;
};
