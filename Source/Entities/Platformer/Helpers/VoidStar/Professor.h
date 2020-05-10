#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Professor : public PlatformerFriendly
{
public:
	static Professor* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Professor(cocos2d::ValueMap& properties);
	virtual ~Professor();

private:
	typedef PlatformerFriendly super;
};
