#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Nessie : public PlatformerFriendly
{
public:
	static Nessie* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Nessie(cocos2d::ValueMap& properties);
	virtual ~Nessie();

private:
	typedef PlatformerFriendly super;
};
