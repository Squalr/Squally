#pragma once

#include <functional>

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

	void push(int value, bool animate = true);
	void pop(std::function<void(int)> callback);
	void updateStackVisibility();
	cocos2d::Vec2 getPositionForStone(int index);

	std::vector<cocos2d::Sprite*> valueStones;
	std::vector<int> values;
	std::vector<ConstantString*> valueStrings;

	cocos2d::Sprite* animatedStone;
	ConstantString* animatedString;

	static const std::string PropertyValues;
	static const int MaxStackSize;
};
