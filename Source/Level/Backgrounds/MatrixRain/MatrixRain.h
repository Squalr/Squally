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

	std::vector<MatrixStrand*> * strands;

	const int strandCount = 32;
};
