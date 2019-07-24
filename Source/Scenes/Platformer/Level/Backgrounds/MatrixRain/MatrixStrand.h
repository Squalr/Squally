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
	void pause(void) override;

	void nextStrandAction();
	void beginStrand();
	void killStrand();

	void randomizeInitialState(int strandIndex);
	void randomizeState(bool spawnInRange);

	std::vector<MatrixLetter*> letters;

	bool isAlive;
	float spawnSpeed;
	int currentLetterIndex;
	int letterCount;
	float elapsedDuration;

	static const int MinLetterCount;
	static const int MaxLetterCount;
	static const float MovementSpeed;
	static const float StrandScale;
	static const float MinSpawnSpeed;
	static const float MaxSpawnSpeed;
	static const float OverFlowY;
	static const float UnderFlowY;
	static const float MinSpawnDistance;
	static const float MaxSpawnDistance;
};
