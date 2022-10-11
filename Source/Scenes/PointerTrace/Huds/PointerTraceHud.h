#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ConstantString;
class LocalizedLabel;

class PointerTraceHud : public Hud
{
public:
	static PointerTraceHud* create();

protected:
	PointerTraceHud();
	virtual ~PointerTraceHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;
	
	void updateRegisters();

	cocos2d::LayerColor* backdrop = nullptr;

	ConstantString* eaxValue = nullptr;
	ConstantString* ebxValue = nullptr;
	ConstantString* ecxValue = nullptr;
	ConstantString* edxValue = nullptr;
	ConstantString* ediValue = nullptr;
	ConstantString* esiValue = nullptr;
	ConstantString* ebpValue = nullptr;
	ConstantString* espValue = nullptr;
	ConstantString* eipValue = nullptr;

	LocalizedLabel* eaxLabel = nullptr;
	LocalizedLabel* ebxLabel = nullptr;
	LocalizedLabel* ecxLabel = nullptr;
	LocalizedLabel* edxLabel = nullptr;
	LocalizedLabel* ediLabel = nullptr;
	LocalizedLabel* esiLabel = nullptr;
	LocalizedLabel* ebpLabel = nullptr;
	LocalizedLabel* espLabel = nullptr;
	LocalizedLabel* eipLabel = nullptr;

	LocalizedLabel* addressHintLabel = nullptr;
	LocalizedLabel* valueHintLabel = nullptr;

	cocos2d::Sprite* movementHelp = nullptr;
};
