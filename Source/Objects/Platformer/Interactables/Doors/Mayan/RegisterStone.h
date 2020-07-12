#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;

class RegisterStone : public InteractObject
{
public:
	static RegisterStone* create(cocos2d::ValueMap& properties);

	void runFx();
	int getValue();
	int getCorrectValue();

	static const std::string MapKey;

protected:
	RegisterStone(cocos2d::ValueMap& properties);
	virtual ~RegisterStone();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract(PlatformerEntity* interactingEntity) override;

private:
	typedef InteractObject super;

	void runAnimationIn(int newValue);
	void runAnimationOut();
	void setValue(int value);
	ConstantString* buildRegisterString();

	InteractObject* pushInteract;
	std::string registerStr;
	int value;
	int correctValue;
	int originalValue;
	cocos2d::Sprite* registerStone;
	cocos2d::Sprite* valueStone;
	ConstantString* valueString;
	LocalizedLabel* valueLabel;
	cocos2d::Sprite* animatedStone;
	ConstantString* animatedString;
	LocalizedLabel* animatedLabel;
	ConstantString* correctValueString;
	LocalizedLabel* correctValueLabel;
	LocalizedLabel* registerLabel;
	cocos2d::Sprite* fxGlow;
	cocos2d::Sprite* fxGlowTop;

	static const std::string PropertyRegister;
	static const std::string PropertyValue;
	static const std::string PropertyCorrectValue;
};
