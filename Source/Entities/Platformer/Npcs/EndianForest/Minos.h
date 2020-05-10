#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Minos : public PlatformerFriendly
{
public:
	static Minos* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Minos(cocos2d::ValueMap& properties);
	virtual ~Minos();

private:
	typedef PlatformerFriendly super;
};
