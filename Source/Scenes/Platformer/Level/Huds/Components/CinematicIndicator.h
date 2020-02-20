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
	virtual ~CinematicIndicator();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::Node* cinematicIndicator;
	cocos2d::Sprite* filmProjector;
	cocos2d::Sprite* reelLarge;
	cocos2d::Sprite* reelSmall;
};
