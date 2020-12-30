#pragma once

#include "Objects/Platformer/Interactables/ToggleableObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;
class WorldSound;

class Brazier : public ToggleableObject
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
		None,
		And,
		Or,
		Xor
	};

	static Brazier* create(cocos2d::ValueMap& properties);

	static TorchColor StrToColor(std::string colorName);
	static Operation StrToOperation(std::string operationName);

	static const std::string MapKey;
	static const std::string MapEventTorchLogicSwitchSavePrefix;
	static const std::string MapEventTorchLogicSwitchPrefix;
	static const std::string MapEventSolveTorches;
	static const std::string MapEventCheckComplete;
	static const std::string PropertyColor;
	static const std::string PropertyOperation;
	static const std::string SaveKeyIsSolved;

protected:
	Brazier(cocos2d::ValueMap& properties);
	virtual ~Brazier();

	void onEnter() override;
	void initializePositions() override;
	void onToggle() override;
	void onEnable() override;
	void onDisable() override;
	void onOptimizationHide() override;
	void onOptimizationShow() override;

private:
	typedef ToggleableObject super;

	bool isSolved();
	void startFx();
	void stopFx();

	cocos2d::Sprite* torch;
	cocos2d::Sprite* glow;
	SmartAnimationSequenceNode* fire;
	WorldSound* burnSound;
	WorldSound* onSound;
	WorldSound* offSound;
	WorldSound* interactSound;

	TorchColor color;
	Operation operation;
	std::string colorName;
	std::string operationName;
	std::string saveKey;

	static const std::string PropertySaveKey;
};
