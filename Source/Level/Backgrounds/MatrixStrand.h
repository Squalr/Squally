#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class MatrixStrand : public Node
{
public:
	static MatrixStrand* create();

private:
	MatrixStrand();
	~MatrixStrand();

	void update(float) override;

	std::string generateLetter();
	void randomizePosition();
	void setLetterCount();

	std::vector<Label*>* letters;

	int letterCount;
	const int minLetterCount = 12;
	const int maxLetterCount = 24;
};
