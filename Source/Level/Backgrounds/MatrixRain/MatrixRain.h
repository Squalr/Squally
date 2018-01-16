#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/Backgrounds/MatrixRain/MatrixStrand.h"

using namespace cocos2d;

class MatrixRain : public Layer
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
