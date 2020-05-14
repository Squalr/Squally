#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class HackableData;
class SmartAnimationSequenceNode;

class LogicTorch : public GameObject
{
public:
	static LogicTorch* create(cocos2d::ValueMap& properties);

	void torchOn();
	void torchOff();

	static const std::string MapKey;

protected:
	LogicTorch(cocos2d::ValueMap& properties);
	virtual ~LogicTorch();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;

	enum class TorchColor
	{
		Red,
		Blue,
		Green,
		Purple
	};

	void updateLogicTorchVisibility();

	cocos2d::Sprite* torch;
	cocos2d::Sprite* glow;
	SmartAnimationSequenceNode* fire;

	bool isOn;
	TorchColor color;

	static const std::string PropertyColor;
	static const std::string PropertyIsOn;
};
