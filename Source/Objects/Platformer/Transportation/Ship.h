#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class Ship : public HackableObject
{
public:
	static Ship* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyShip;

protected:
	Ship(cocos2d::ValueMap& properties);
	virtual ~Ship();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	cocos2d::Sprite* hull;
};
