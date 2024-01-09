#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class WorldSound;

class Icicle : public HackableObject
{
public:
	static Icicle* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Icicle(cocos2d::ValueMap& properties);
	virtual ~Icicle();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void applyGravity(float dt);
	bool isFalling = false;
	bool unregisterHackables = false;
	bool runOnce = false;
	bool noSound = false;

	cocos2d::Sprite* sprite = nullptr;
	CollisionObject* collision = nullptr;
	WorldSound* rumbleSound = nullptr;
	WorldSound* fallSound = nullptr;

	static const std::string PropertyUnregisterHackables;
	static const std::string PropertyRunOnce;
	static const std::string PropertyNoSound;
};
