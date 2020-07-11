#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;

class StoneStack : public GameObject
{
public:
	static StoneStack* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	StoneStack(cocos2d::ValueMap& properties);
	virtual ~StoneStack();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	void push(int value);
	int pop();
	void updateStackVisibility();

	std::vector<cocos2d::Sprite*> valueStones;
	std::vector<int> values;
	std::vector<ConstantString*> valueStrings;

	static const std::string PropertyValues;
	static const int MaxStackSize;
};
