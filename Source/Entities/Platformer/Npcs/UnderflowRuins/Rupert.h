#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Rupert : public PlatformerFriendly
{
public:
	static Rupert* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Rupert(cocos2d::ValueMap& properties);
	virtual ~Rupert();

private:
	typedef PlatformerFriendly super;
};
