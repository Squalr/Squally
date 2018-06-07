#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/UILayer.h"
#include "Resources.h"

#include "MatrixStrand.h"

using namespace cocos2d;

class MatrixRain : public UILayer
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
