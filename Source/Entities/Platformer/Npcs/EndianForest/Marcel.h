#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Marcel : public PlatformerFriendly
{
public:
	static Marcel* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Marcel(cocos2d::ValueMap& properties);
	virtual ~Marcel();

private:
	typedef PlatformerFriendly super;
};
