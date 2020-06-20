#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class ReanimatedPig : public PlatformerEnemy
{
public:
	static ReanimatedPig* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	ReanimatedPig(cocos2d::ValueMap& properties);
	virtual ~ReanimatedPig();

private:
	typedef PlatformerEnemy super;
};
