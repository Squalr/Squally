#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Polyphemus : public PlatformerFriendly
{
public:
	static Polyphemus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Polyphemus(cocos2d::ValueMap& properties);
	virtual ~Polyphemus();

private:
	typedef PlatformerFriendly super;
};
