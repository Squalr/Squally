#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Ysara : public PlatformerFriendly
{
public:
	static Ysara* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Ysara(cocos2d::ValueMap& properties);
	virtual ~Ysara();

private:
	typedef PlatformerFriendly super;
};
