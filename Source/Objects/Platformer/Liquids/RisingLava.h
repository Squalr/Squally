#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class RisingLava : public HackableObject
{
public:
	static RisingLava* create(cocos2d::ValueMap& properties);

	void activate();

	static const std::string HackIdentifierRisingLava;
	static const std::string MapKey;

protected:
	RisingLava(cocos2d::ValueMap& properties);
	virtual ~RisingLava();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void raiseLava(float dt);

	bool isActive = false;
	cocos2d::CSize lavaSize;
	Lava* lava = nullptr;
	
	static const float Speed;
};
