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
	static TorchColor StrToColor(std::string torchColorName);

	TorchColor getTorchColor();

	static const std::string MapKey;

protected:
	Brazier(cocos2d::ValueMap& properties);
	virtual ~Brazier();

	void onEnter() override;
	void initializePositions() override;
	void onToggle(bool isInstant = true) override;
	void onEnable(bool isInit, bool isInstant = true) override;
	void onDisable(bool isInit, bool isInstant = true) override;
	void onOptimizationHide() override;
	void onOptimizationShow() override;

private:
	typedef ToggleableObject super;

	bool isSolved();
	void startFx();
	void stopFx();

	cocos2d::Sprite* torch = nullptr;
	cocos2d::Sprite* glow = nullptr;
	SmartAnimationSequenceNode* fire = nullptr;
	WorldSound* burnSound = nullptr;
	WorldSound* onSound = nullptr;
	WorldSound* offSound = nullptr;
	WorldSound* interactSound = nullptr;

	TorchColor torchColor = TorchColor::Red;
	std::string torchColorName;
	std::string operationName;
};
