#pragma once

#include "cocos/math/CCGeometry.h"

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class CurrencyInventory;
class EquipmentInventory;
class HackablePreview;
class HexusOpponentData;
class Inventory;
class SmartAnimationNode;
class SpeechBubble;

class PlatformerEntity : public HackableObject
{
public:
	enum class ControlState
	{
		Normal,
		Swimming,
	};

	std::string getEntityName();
	virtual float getFloatHeight();

	Inventory* getInventory();
	EquipmentInventory* getEquipmentInventory();
	CurrencyInventory* getCurrencyInventory();
	float getScale();
	std::string getAnimationResource();
	std::string getEmblemResource();
	SmartAnimationNode* getAnimations();
	cocos2d::Size getEntitySize();
	cocos2d::Size getMovementSize();
	cocos2d::Vec2 getCollisionOffset();
	float getHoverHeight();
	HexusOpponentData* getHexusOpponentData();
	virtual cocos2d::Vec2 getAvatarFrameOffset() = 0;
	virtual void performSwimAnimation();
	virtual void performJumpAnimation();

	ControlState controlState;
	SpeechBubble* speechBubble;
	SmartAnimationNode* animationNode;

protected:
	PlatformerEntity(
		cocos2d::ValueMap& properties,
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
	~PlatformerEntity();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;

	std::string state;

	HexusOpponentData* hexusOpponentData;
	Inventory* inventory;
	EquipmentInventory* equipmentInventory;
	CurrencyInventory* currencyInventory;

	static const std::string MapKeyPropertyState;

private:
	typedef HackableObject super;
	
	float entityScale;
	cocos2d::Vec2 entityCollisionOffset;
	cocos2d::Size entitySize;
	cocos2d::Size movementSize;
	float hoverHeight;
	std::string entityName;
	std::string animationResource;
	std::string emblemResource;
	cocos2d::Vec2 hackButtonOffset;
};
