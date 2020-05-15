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
	enum class TorchColor
	{
		Red,
		Blue,
		Green,
		Purple
	};

	enum class Operation
	{
		And,
		Or,
		Xor
	};

	static LogicTorch* create(cocos2d::ValueMap& properties);

	static TorchColor StrToColor(std::string colorName);
	static Operation StrToOperation(std::string operationName);

	void torchOn();
	void torchOff();

	static const std::string MapKey;
	static const std::string EventTorchLogicSwitchPrefix;
	static const std::string PropertyColor;
	static const std::string PropertyOperation;

protected:
	LogicTorch(cocos2d::ValueMap& properties);
	virtual ~LogicTorch();

	void onEnter() override;
	void initializePositions() override;
	void onInteract() override;

private:
	typedef InteractObject super;

	void updateLogicTorchVisibility();

	cocos2d::Sprite* torch;
	cocos2d::Sprite* glow;
	SmartAnimationSequenceNode* fire;

	bool isOn;
	TorchColor color;
	Operation operation;
	std::string saveKey;

	static const std::string PropertyIsOn;
	static const std::string PropertyIsInteractable;
	static const std::string PropertySaveKey;
};
