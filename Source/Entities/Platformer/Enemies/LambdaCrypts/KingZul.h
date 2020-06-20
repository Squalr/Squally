#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class KingZul : public PlatformerEnemy
{
public:
	static KingZul* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	KingZul(cocos2d::ValueMap& properties);
	virtual ~KingZul();

private:
	typedef PlatformerEnemy super;
};
