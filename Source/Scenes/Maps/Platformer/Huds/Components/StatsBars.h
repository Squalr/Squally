#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class StatsBars : public SmartNode
{
public:
	static StatsBars* create();

private:
	typedef SmartNode super;
	StatsBars();
	virtual ~StatsBars() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	cocos2d::Sprite* heart;
	cocos2d::Sprite* heartFrame;
	cocos2d::Sprite* heartBar;
	cocos2d::Sprite* special;
	cocos2d::Sprite* specialFrame;
	cocos2d::Sprite* specialBar;

	std::vector<cocos2d::Sprite*> emptyRunes;
	std::vector<cocos2d::Sprite*> filledRunes;

	static const int RuneCount;
};
