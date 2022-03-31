#pragma once

#include "Entities/Platformer/PlatformerFriendly.h"

namespace cocos2d
{
	typedef std::map<std::string, Value> ValueMap;
}

class TopDownSqually : public PlatformerFriendly
{
public:
	static TopDownSqually* create();
	static TopDownSqually* deserialize(cocos2d::ValueMap& properties);
	
	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	std::vector<std::string> getWalkSounds() override;

	static const std::string MapKey;
	static const std::string TeamTag;

protected:
	TopDownSqually(cocos2d::ValueMap& properties);
	virtual ~TopDownSqually();
	
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef PlatformerFriendly super;

	static const float TopDownSquallyScale;
};
