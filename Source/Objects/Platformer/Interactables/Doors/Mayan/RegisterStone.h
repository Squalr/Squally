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

	InteractObject* pushInteract = nullptr;
	std::string registerStr;
	int value = 0;
	int correctValue = 0;
	int originalValue = 0;
	cocos2d::Sprite* registerStone = nullptr;
	cocos2d::Sprite* valueStone = nullptr;
	ConstantString* valueString = nullptr;
	LocalizedLabel* valueLabel = nullptr;
	cocos2d::Sprite* animatedStone = nullptr;
	ConstantString* animatedString = nullptr;
	LocalizedLabel* animatedLabel = nullptr;
	ConstantString* correctValueString = nullptr;
	LocalizedLabel* correctValueLabel = nullptr;
	LocalizedLabel* registerLabel = nullptr;
	cocos2d::Sprite* fxGlow = nullptr;
	cocos2d::Sprite* fxGlowTop = nullptr;

	static const std::string PropertyRegister;
	static const std::string PropertyValue;
	static const std::string PropertyCorrectValue;
};
