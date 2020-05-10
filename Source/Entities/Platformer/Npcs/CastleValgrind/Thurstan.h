#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Thurstan : public PlatformerFriendly
{
public:
	static Thurstan* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Thurstan(cocos2d::ValueMap& properties);
	virtual ~Thurstan();

private:
	typedef PlatformerFriendly super;
};
