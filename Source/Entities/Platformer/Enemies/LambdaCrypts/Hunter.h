#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Hunter : public PlatformerEnemy
{
public:
	static Hunter* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Hunter(cocos2d::ValueMap& properties);
	virtual ~Hunter();

private:
	typedef PlatformerEnemy super;
};
