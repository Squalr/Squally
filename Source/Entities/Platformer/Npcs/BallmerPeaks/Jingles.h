#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Jingles : public PlatformerFriendly
{
public:
	static Jingles* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Jingles(cocos2d::ValueMap& properties);
	virtual ~Jingles();

private:
	typedef PlatformerFriendly super;
};
