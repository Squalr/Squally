#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Hera : public PlatformerFriendly
{
public:
	static Hera* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Hera(cocos2d::ValueMap& properties);
	virtual ~Hera();

private:
	typedef PlatformerFriendly super;
};
