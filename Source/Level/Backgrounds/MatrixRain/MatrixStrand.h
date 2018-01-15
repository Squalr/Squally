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

	void update(float) override;

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

	static const float movementSpeed;
	static const int minLetterCount;
	static const int maxLetterCount;
};
