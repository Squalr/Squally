#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Radon : public PlatformerFriendly
{
public:
	static Radon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Radon(cocos2d::ValueMap& properties);
	virtual ~Radon();

private:
	typedef PlatformerFriendly super;
};
