#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class TrapDoorFrame : public GameObject
{
public:
	static TrapDoorFrame* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	TrapDoorFrame(cocos2d::ValueMap& properties);
	virtual ~TrapDoorFrame();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;

	bool isFlipped;
	cocos2d::Sprite* trapDoorFrame;
};
