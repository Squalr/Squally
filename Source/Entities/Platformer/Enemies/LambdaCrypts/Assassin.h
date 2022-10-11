#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class Assassin : public PlatformerEnemy
{
public:
	static Assassin* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Assassin(cocos2d::ValueMap& properties);
	virtual ~Assassin();

private:
	typedef PlatformerEnemy super;
};
