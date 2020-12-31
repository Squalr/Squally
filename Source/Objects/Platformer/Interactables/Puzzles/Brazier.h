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

	static Brazier* create(cocos2d::ValueMap& properties);

	static TorchColor StrToColor(std::string colorName);

	static const std::string MapKey;

protected:
	Brazier(cocos2d::ValueMap& properties);
	virtual ~Brazier();

	void onEnter() override;
	void initializePositions() override;
	void onToggle() override;
	void onEnable(bool isInit) override;
	void onDisable(bool isInit) override;
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
	std::string colorName;
	std::string operationName;
	std::string saveKey;

	static const std::string PropertySaveKey;
};
