#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class WorldSound;

class ReactorCore : public InteractObject
{
public:
	static ReactorCore* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ReactorCore(cocos2d::ValueMap& properties);
	virtual ~ReactorCore();

	void onEnter() override;
	void initializePositions() override;
	void onInteract(PlatformerEntity* interactingEntity) override;

private:
	typedef InteractObject super;

	cocos2d::Sprite* reactorCore = nullptr;
	cocos2d::Sprite* reactorPad = nullptr;
	cocos2d::Sprite* reactorCase = nullptr;
	WorldSound* reactorSfx = nullptr;
};
