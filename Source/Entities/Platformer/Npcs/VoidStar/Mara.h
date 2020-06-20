#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Mara : public PlatformerFriendly
{
public:
	static Mara* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Mara(cocos2d::ValueMap& properties);
	virtual ~Mara();

private:
	typedef PlatformerFriendly super;
};
