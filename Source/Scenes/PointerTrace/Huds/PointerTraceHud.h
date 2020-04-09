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

	cocos2d::LayerColor* backdrop;

	ConstantString* eaxValue;
	ConstantString* ebxValue;
	ConstantString* ecxValue;
	ConstantString* edxValue;
	ConstantString* ediValue;
	ConstantString* esiValue;
	ConstantString* ebpValue;
	ConstantString* espValue;
	ConstantString* eipValue;

	LocalizedLabel* eaxLabel;
	LocalizedLabel* ebxLabel;
	LocalizedLabel* ecxLabel;
	LocalizedLabel* edxLabel;
	LocalizedLabel* ediLabel;
	LocalizedLabel* esiLabel;
	LocalizedLabel* ebpLabel;
	LocalizedLabel* espLabel;
	LocalizedLabel* eipLabel;

	LocalizedLabel* addressHintLabel;
	LocalizedLabel* valueHintLabel;

	cocos2d::Sprite* movementHelp;
};
