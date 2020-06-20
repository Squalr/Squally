#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class QueenLiana : public PlatformerFriendly
{
public:
	static QueenLiana* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	QueenLiana(cocos2d::ValueMap& properties);
	virtual ~QueenLiana();

private:
	typedef PlatformerFriendly super;
};
