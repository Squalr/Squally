#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Celeste : public PlatformerFriendly
{
public:
	static Celeste* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Celeste(cocos2d::ValueMap& properties);
	virtual ~Celeste();

private:
	typedef PlatformerFriendly super;
};
