#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Lycan : public PlatformerFriendly
{
public:
	static Lycan* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Lycan(cocos2d::ValueMap& properties);
	virtual ~Lycan();

private:
	typedef PlatformerFriendly super;
};
