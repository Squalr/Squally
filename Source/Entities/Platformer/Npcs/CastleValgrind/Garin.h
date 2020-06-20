#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Garin : public PlatformerFriendly
{
public:
	static Garin* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Garin(cocos2d::ValueMap& properties);
	virtual ~Garin();

private:
	typedef PlatformerFriendly super;
};
