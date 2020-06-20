#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Garrick : public PlatformerFriendly
{
public:
	static Garrick* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Garrick(cocos2d::ValueMap& properties);
	virtual ~Garrick();

private:
	typedef PlatformerFriendly super;
};
