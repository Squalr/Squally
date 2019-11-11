#pragma once

#include "Entities/Platformer/PlatformerEntity.h"

class ClickableNode;

// Base class for player + npcs
class PlatformerFriendly : public PlatformerEntity
{
public:
	static const std::string PlatformerFriendlyTag;

protected:
	PlatformerFriendly(cocos2d::ValueMap& properties,
		std::string entityName,
		std::string scmlResource,
		std::string emblemResource,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		float hoverHeight = 0.0f,
		std::string inventorySaveKey = "",
		std::string equipmentSaveKey = "",
		std::string currencySaveKey = "");
	~PlatformerFriendly();

private:
	typedef PlatformerEntity super;
};
