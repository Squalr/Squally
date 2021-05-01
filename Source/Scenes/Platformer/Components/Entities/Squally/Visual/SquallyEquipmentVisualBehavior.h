#pragma once

#include "Engine/Components/Component.h"

class ConstantString;
class LocalizedLabel;
class Squally;

class SquallyEquipmentVisualBehavior : public Component
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
	typedef Component super;
	
	void updateEquipmentVisual();

	cocos2d::Vec2 debugOffset;

	cocos2d::Node* debugHud;
	ConstantString* debugOffsetXStr;
	ConstantString* debugOffsetYStr;
	LocalizedLabel* debugOffsetXLabel;
	LocalizedLabel* debugOffsetYLabel;

	Squally* squally;

	static const bool InvertDebugControls;
};
