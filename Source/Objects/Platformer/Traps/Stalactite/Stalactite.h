#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class Stalactite : public HackableObject
{
public:
	static Stalactite* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Stalactite(cocos2d::ValueMap& properties);
	virtual ~Stalactite();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	void updateStalactite();
	float getTravelHeight();
	std::vector<cocos2d::Vec2> createSpikeCollision();

	volatile float travelDistance;
	cocos2d::Node* heavenHugContainer;
	cocos2d::Sprite* heavenHug;
	CollisionObject* spikeCollision;

	static const float SpeedPer480Px;
};
