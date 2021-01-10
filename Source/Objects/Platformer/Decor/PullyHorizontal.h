#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;

class PullyHorizontal : public GameObject
{
public:
	static PullyHorizontal* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	PullyHorizontal(cocos2d::ValueMap& properties);
	virtual ~PullyHorizontal();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;
	
	cocos2d::Sprite* wheelLeft;
	cocos2d::Sprite* wheelRight;
	SmartAnimationSequenceNode* rope;
};
