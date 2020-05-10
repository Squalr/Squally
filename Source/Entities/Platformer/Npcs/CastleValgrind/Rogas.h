#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Rogas : public PlatformerFriendly
{
public:
	static Rogas* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Rogas(cocos2d::ValueMap& properties);
	virtual ~Rogas();

private:
	typedef PlatformerFriendly super;
};
