#pragma once

#include "Objects/Platformer/Interactables/Mounts/MountBase.h"

namespace cocos2d
{
	class Sprite;
}

class Music;
class SmartAnimationNode;

class GatlingGun : public MountBase
{
public:
	static GatlingGun* create(cocos2d::ValueMap& properties);

	void mount(PlatformerEntity* interactingEntity) override;
	void dismount(PlatformerEntity* entity) override;
	SmartAnimationNode* getAnimations() const;

	void playGauntletTrack();
	void stopGauntletTrack();

	static const std::string MapKey;

protected:
	GatlingGun(cocos2d::ValueMap& properties);
	virtual ~GatlingGun();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Vec2 getReparentPosition(PlatformerEntity* entity) override;

private:
	typedef MountBase super;

	void updateCanMove();

	SmartAnimationNode* animations = nullptr;
	cocos2d::Sprite* body = nullptr;
	Music* gauntletMusic = nullptr;

	static const std::string PropertyColor;
};
