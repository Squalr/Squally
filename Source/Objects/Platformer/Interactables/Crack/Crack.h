#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class Crack : public InteractObject
{
public:
	static Crack* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string MapPropertyCrackSize;

protected:
	Crack(cocos2d::ValueMap& properties);
	virtual ~Crack();

	void initializePositions() override;
	void onInteract(PlatformerEntity* interactingEntity) override;

private:
	typedef InteractObject super;

	cocos2d::Sprite* crack = nullptr;
	std::string crackSize;
};
