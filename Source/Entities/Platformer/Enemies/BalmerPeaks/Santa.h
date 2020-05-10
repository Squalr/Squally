#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Santa : public PlatformerEnemy
{
public:
	static Santa* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Santa(cocos2d::ValueMap& properties);
	virtual ~Santa();

private:
	typedef PlatformerEnemy super;
};
