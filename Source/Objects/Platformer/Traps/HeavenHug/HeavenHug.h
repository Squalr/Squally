#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class HeavenHug : public HackableObject
{
public:
	static HeavenHug* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyHeavenHug;

protected:
	HeavenHug(cocos2d::ValueMap& initProperties);
	virtual ~HeavenHug();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	void updateHeavenHug();
	float getTravelHeight();
	cocos2d::PhysicsBody* createSpikeCollision();

	volatile float travelDistance;
	cocos2d::Node* heavenHugContainer;
	cocos2d::Sprite* heavenHug;
	CollisionObject* spikeCollision;

	static const float SpeedPer480Px;
};
