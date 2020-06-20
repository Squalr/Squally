#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Johann : public PlatformerFriendly
{
public:
	static Johann* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Johann(cocos2d::ValueMap& properties);
	virtual ~Johann();

private:
	typedef PlatformerFriendly super;
};
