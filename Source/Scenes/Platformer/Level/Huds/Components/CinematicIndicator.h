#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CinematicIndicator : public SmartNode
{
public:
	static CinematicIndicator* create();

protected:
	CinematicIndicator();
	~CinematicIndicator();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* cinematicIndicator;
	cocos2d::Sprite* filmProjector;
	cocos2d::Sprite* reelLarge;
	cocos2d::Sprite* reelSmall;
};
