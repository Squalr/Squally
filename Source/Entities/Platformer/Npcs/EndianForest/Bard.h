#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Bard : public PlatformerFriendly
{
public:
	static Bard* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Bard(cocos2d::ValueMap& properties);
	virtual ~Bard();

private:
	typedef PlatformerFriendly super;
};
