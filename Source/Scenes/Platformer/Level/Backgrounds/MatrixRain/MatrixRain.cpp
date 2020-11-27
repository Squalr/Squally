#include "MatrixRain.h"

#include "Scenes/Platformer/Level/Backgrounds/MatrixRain/MatrixStrand.h"

using namespace cocos2d;

const int MatrixRain::strandCount = 32;

MatrixRain* MatrixRain::create()
{
	MatrixRain* matrixRain = new MatrixRain();

	matrixRain->autorelease();

	return matrixRain;
}

MatrixRain::MatrixRain()
{
	return;
	this->strands = std::vector<MatrixStrand*>();

	// Initialize strands
	for (int index = 0; index < MatrixRain::strandCount; index++)
	{
		MatrixStrand* strand = MatrixStrand::create(index);

		this->strands.push_back(strand);
		this->addChild(strand);
	}

}

MatrixRain::~MatrixRain()
{
}

void MatrixRain::pause()
{
	// Ignore pause
}
