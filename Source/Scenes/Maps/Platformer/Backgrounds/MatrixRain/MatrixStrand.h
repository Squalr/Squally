#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Action;
}

class MatrixLetter;

class MatrixStrand : public SmartNode
{
public:
	static MatrixStrand* create(int strandIndex);

private:
	typedef SmartNode super;
	MatrixStrand(int strandIndex);
	~MatrixStrand();

	void onEnter() override;
	void update(float) override;
	virtual void pause(void) override;

	void nextStrandAction();
	void beginStrand();
	void killStrand();

	void randomizePosition();
	void setLetterCount();

	std::vector<MatrixLetter*> letters;

	cocos2d::Action* updateAction;
	float spawnSpeed;
	int currentLetterIndex;
	int letterCount;

	static const int minLetterCount;
	static const int maxLetterCount;
	static const float movementSpeed;
	static const float strandScale;
	static const float minSpawnSpeed;
	static const float maxSpawnSpeed;
	static const float overFlowY;
	static const float underFlowY;
	static const float minSpawnDistance;
	static const float maxSpawnDistance;
};
