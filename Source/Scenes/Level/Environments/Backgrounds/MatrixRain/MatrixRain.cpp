#include "MatrixRain.h"

const int MatrixRain::strandCount = 32;

MatrixRain* MatrixRain::create()
{
	MatrixRain* matrixRain = new MatrixRain();

	matrixRain->autorelease();

	return matrixRain;
}

MatrixRain::MatrixRain()
{
	this->strands = new std::vector<MatrixStrand*>();

	// Initialize strands
	for (int index = 0; index < MatrixRain::strandCount; index++)
	{
		MatrixStrand* strand = MatrixStrand::create(index);

		this->strands->push_back(strand);
		this->addChild(strand);
	}

	this->scheduleUpdate();
}

MatrixRain::~MatrixRain()
{
	delete(this->strands);
}

void MatrixRain::pause()
{
	// Ignore pause
}

void MatrixRain::setPositions()
{
}
