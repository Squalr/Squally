#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Alder : public PlatformerFriendly
{
public:
	static Alder* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Alder(cocos2d::ValueMap& properties);
	virtual ~Alder();

private:
	typedef PlatformerFriendly super;
};
