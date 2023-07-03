#pragma once

#include <functional>

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class WorldSound;

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

	void popAll(std::function<void()> callback = nullptr);
	void pushAll(std::function<void()> callback = nullptr, bool animate = true);
	void push(int value, bool unlockInteraction = true, bool animate = true, std::function<void()> callback = nullptr);
	void pop(bool unlockInteraction = true, std::function<void(int)> callback = nullptr);
	void updateStackVisibility();
	cocos2d::Vec2 getPositionForStone(int index);

	std::vector<cocos2d::Sprite*> valueStones;
	std::vector<int> values;
	std::vector<int> originalValues;
	std::vector<int> pushList;
	std::vector<ConstantString*> valueStrings;

	WorldSound* popSfx = nullptr;
	cocos2d::Sprite* animatedStone = nullptr;
	ConstantString* animatedString = nullptr;

	static const std::string PropertyValues;
	static const int MaxStackSize;
};
