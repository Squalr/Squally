#pragma once
#include "cocos2d.h"

#include "Engine/UI/HUD/Hud.h"

#include "MatrixStrand.h"

using namespace cocos2d;

class MatrixRain : public Hud
{
public:
	static MatrixRain* create();

private:
	MatrixRain();
	~MatrixRain();

	virtual void pause(void) override;
	void setPositions();

	std::vector<MatrixStrand*> * strands;

	static const int strandCount;
};
