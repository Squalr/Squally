#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class FrostFiend : public PlatformerEnemy
{
public:
	static FrostFiend* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	FrostFiend(cocos2d::ValueMap& properties);
	virtual ~FrostFiend();

private:
	typedef PlatformerEnemy super;
};
