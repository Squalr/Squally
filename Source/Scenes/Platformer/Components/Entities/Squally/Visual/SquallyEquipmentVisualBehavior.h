#pragma once

#include "Engine/Components/GameComponent.h"

class ConstantString;
class LocalizedLabel;
class Squally;

class SquallyEquipmentVisualBehavior : public GameComponent
{
public:
	static SquallyEquipmentVisualBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyEquipmentVisualBehavior(GameObject* owner);
	virtual ~SquallyEquipmentVisualBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void updateEquipmentVisual();

	cocos2d::Vec2 debugOffset;

	cocos2d::Node* debugHud;
	ConstantString* debugOffsetXStr;
	ConstantString* debugOffsetYStr;
	LocalizedLabel* debugOffsetXLabel;
	LocalizedLabel* debugOffsetYLabel;

	Squally* squally = nullptr;

	static const bool InvertDebugControls;
};
