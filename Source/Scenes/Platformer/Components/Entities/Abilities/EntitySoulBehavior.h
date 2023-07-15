#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class MinMaxPool;
class PlatformerEntity;
class PocketPoolDeserializer;
class SmartAnimationSequenceNode;
class SmartParticles;
class Squally;
class WorldSound;

class EntitySoulBehavior : public GameComponent
{
public:
	static EntitySoulBehavior* create(GameObject* owner);
	
	bool canSoulHarvest(bool checkZ);
	bool wasSoulHarvested();

	static const std::string MapKey;

protected:
	EntitySoulBehavior(GameObject* owner);
	virtual ~EntitySoulBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void attemptSoulHarvest();
	void onSoulHarvested();
	void updateIconVisibility();
	void refreshCursorState();

	PlatformerEntity* entity = nullptr;
	Squally* squally = nullptr;
	cocos2d::Sprite* soulHarvestIcon = nullptr;
	SmartParticles* soulFx = nullptr;
	SmartAnimationSequenceNode* soulHarvestFx = nullptr;
	SmartAnimationSequenceNode* healFxSqually = nullptr;
	WorldSound* soulHarvestSfx = nullptr;

	std::string currentHelperName;

	static const std::string SavePropertyKeyWasSoulHarvested;
};
