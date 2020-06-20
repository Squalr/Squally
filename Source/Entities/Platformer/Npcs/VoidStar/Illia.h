#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Illia : public PlatformerFriendly
{
public:
	static Illia* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Illia(cocos2d::ValueMap& properties);
	virtual ~Illia();

private:
	typedef PlatformerFriendly super;
};
