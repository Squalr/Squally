#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/Backgrounds/MatrixRain/MatrixLetter.h"

using namespace cocos2d;

class MatrixStrand : public Node
{
public:
	static MatrixStrand* create();

private:
	MatrixStrand();
	~MatrixStrand();

	void nextStrandAction();
	void beginStrand();
	void endStrand();
	void randomizePosition();
	float getUpdateSpeed();
	void setLetterCount();

	std::vector<MatrixLetter*>* letters;

	Action* updateAction;
	int currentLetterIndex;
	int letterCount;
	const int minLetterCount = 28;
	const int maxLetterCount = 40;
};
