#pragma once

#include "Objects/Platformer/Collectables/Collectable.h"

class SmartParticles;
class WorldSound;

class ManaOrb : public Collectable
{
public:
	static ManaOrb* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	ManaOrb(cocos2d::ValueMap& properties);
	virtual ~ManaOrb();

	void onEnter() override;
	void initializeListeners() override;
	void hideCollectable() override;

private:
	typedef Collectable super;

	SmartParticles* manaOrb;
	WorldSound* collectSound;
};
