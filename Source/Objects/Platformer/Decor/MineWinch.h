#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationNode;

class MineWinch : public GameObject
{
public:
	static MineWinch* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MineWinch(cocos2d::ValueMap& properties);
	virtual ~MineWinch();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	void runAnimation();

	SmartAnimationNode* mineClawAnimations;
};
