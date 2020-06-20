#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Robin : public PlatformerFriendly
{
public:
	static Robin* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Robin(cocos2d::ValueMap& properties);
	virtual ~Robin();

private:
	typedef PlatformerFriendly super;
};
