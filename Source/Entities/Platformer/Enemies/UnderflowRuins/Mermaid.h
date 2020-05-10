#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Mermaid : public PlatformerEnemy
{
public:
	static Mermaid* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Mermaid(cocos2d::ValueMap& properties);
	virtual ~Mermaid();

private:
	typedef PlatformerEnemy super;
};
