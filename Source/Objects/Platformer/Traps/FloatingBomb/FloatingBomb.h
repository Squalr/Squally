#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class FloatingBomb : public HackableObject
{
public:
	static FloatingBomb* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyFloatingBomb;

protected:
	FloatingBomb(cocos2d::ValueMap& initProperties);
	virtual ~FloatingBomb();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	cocos2d::Sprite* bomb;
	CollisionObject* bombCollision;
};
