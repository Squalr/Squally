#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
};

class HackableData;
class SmartAnimationSequenceNode;

class LogicTorch : public InteractObject
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
	void onInteract() override;

private:
	typedef InteractObject super;

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
	std::string saveKey;

	static const std::string PropertyColor;
	static const std::string PropertyIsOn;
	static const std::string PropertyIsInteractable;
	static const std::string PropertySaveKey;
	static const std::string EventTorchLogicSwitchPrefix;
};
