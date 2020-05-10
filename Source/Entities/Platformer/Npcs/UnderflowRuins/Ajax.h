#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Ajax : public PlatformerFriendly
{
public:
	static Ajax* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Ajax(cocos2d::ValueMap& properties);
	virtual ~Ajax();

private:
	typedef PlatformerFriendly super;
};
