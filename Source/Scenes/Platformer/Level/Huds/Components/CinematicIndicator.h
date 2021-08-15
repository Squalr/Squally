#pragma once
#include <functional>

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

	cocos2d::Node* cinematicIndicator = nullptr;
	cocos2d::Sprite* filmProjector = nullptr;
	cocos2d::Sprite* reelLarge = nullptr;
	cocos2d::Sprite* reelSmall = nullptr;
};
