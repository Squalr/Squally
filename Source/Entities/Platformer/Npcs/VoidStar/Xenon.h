#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Xenon : public PlatformerFriendly
{
public:
	static Xenon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Xenon(cocos2d::ValueMap& properties);
	virtual ~Xenon();

private:
	typedef PlatformerFriendly super;
};
