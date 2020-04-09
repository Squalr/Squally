#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class OrcSwordsman : public PlatformerEnemy
{
public:
	static OrcSwordsman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	
	static const std::string MapKey;
	
protected:
	OrcSwordsman(cocos2d::ValueMap& properties);
	virtual ~OrcSwordsman();

private:
	typedef PlatformerEnemy super;
};
