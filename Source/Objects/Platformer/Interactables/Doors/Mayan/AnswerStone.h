#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;

class AnswerStone : public GameObject
{
public:
	static AnswerStone* create(cocos2d::ValueMap& properties);

	void runFx();
	int getCorrectValue();

	static const std::string MapKey;

protected:
	AnswerStone(cocos2d::ValueMap& properties);
	virtual ~AnswerStone();

	void initializePositions() override;

private:
	typedef GameObject super;

	int correctValue = 0;
	cocos2d::Sprite* answerStone = nullptr;
	ConstantString* correctValueString = nullptr;
	LocalizedLabel* correctValueLabel = nullptr;

	static const std::string PropertyRegister;
	static const std::string PropertyCorrectValue;
};
