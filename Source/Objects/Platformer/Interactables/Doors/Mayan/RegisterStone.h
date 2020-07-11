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

	static const std::string MapKey;

protected:
	RegisterStone(cocos2d::ValueMap& properties);
	virtual ~RegisterStone();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef InteractObject super;

	void setValue(int value);
	ConstantString* buildRegisterString();

	std::string registerStr;
	int value;
	cocos2d::Sprite* registerStone;
	cocos2d::Sprite* valueStone;
	ConstantString* valueString;
	LocalizedLabel* valueLabel;
	LocalizedLabel* registerLabel;

	static const std::string PropertyRegister;
	static const std::string PropertyValue;
};
