#pragma once
#include "cocos2d.h"
#include "udis86.h"
#include "fasm.h"
#include "Collision/CollisionObject.h"
#include "GUI/Components/OutlineLabel.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class InstructionTest : public CollisionObject
{
public:
	static InstructionTest* create();

	void hackableFunction();

protected:
	InstructionTest();
	~InstructionTest();

private:
	void update(float) override;

	Sprite * sprite;
	OutlineLabel * instructionLabel;

	float elapsed = 0.0f;
};
