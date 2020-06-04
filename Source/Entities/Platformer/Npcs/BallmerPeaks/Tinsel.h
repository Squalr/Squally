#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Tinsel : public PlatformerFriendly
{
public:
	static Tinsel* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Tinsel(cocos2d::ValueMap& properties);
	virtual ~Tinsel();

private:
	typedef PlatformerFriendly super;
};
