#pragma once

#include "cocos/math/CCGeometry.h"

#include "Engine/Hackables/HackableObject.h"

class HackablePreview;
class HexusOpponentData;
class LocalizedString;
class PlatformerEntityDeserializer;
class SmartAnimationNode;

class PlatformerEntity : public HackableObject
{
public:
	enum class ControlState
	{
		None,
		Normal,
		Swimming,
	};

	std::string getEntityKey();
	virtual float getFloatHeight();

	float getScale();
	std::string getAnimationResource();
	std::string getEmblemResource();
	cocos2d::Node* getFloatNode();
	SmartAnimationNode* getAnimations();
	cocos2d::Size getEntitySize();
	cocos2d::Size getMovementSize();
	cocos2d::Vec2 getCollisionOffset();
	cocos2d::Vec2 getEntityCenterPoint();
	float getHoverHeight();
	virtual cocos2d::Vec2 getDialogueOffset() = 0;
	virtual LocalizedString* getEntityName() = 0;
	virtual std::string getSwimAnimation();
	virtual std::string getJumpAnimation();
	virtual std::string getJumpSound();
	virtual std::vector<std::string> getSwimSounds();
	PlatformerEntity::ControlState getControlState();
	bool isFlippedX();
	bool isFlippedY();
	PlatformerEntity* uiClone();
	std::string getBattleBehavior();

	ControlState controlState;
	ControlState controlStateOverride;

	static const std::string PlatformerEntityTag;
	static const std::string MapKeyBattleAttachedBehavior;

protected:
	PlatformerEntity(
		cocos2d::ValueMap& properties,
		std::string entityName,
		std::string scmlResource,
		std::string emblemResource,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		float hoverHeight = 0.0f);
	virtual ~PlatformerEntity();
	
	void onEnter() override;
	void update(float dt) override;
	cocos2d::Vec2 getRainOffset() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;

	std::string state;

	cocos2d::Node* floatNode;
	cocos2d::Node* belowAnimationNode;
	SmartAnimationNode* animationNode;

	HexusOpponentData* hexusOpponentData;

	static const std::string MapKeyPropertyState;

private:
	typedef HackableObject super;

	void optimizationHideOffscreenEntity();
	
	float entityScale;
	cocos2d::Vec2 entityCollisionOffset;
	cocos2d::Size entitySize;
	cocos2d::Size movementSize;
	float hoverHeight;
	std::string entityName;
	std::string animationResource;
	std::string emblemResource;
	cocos2d::Vec2 hackButtonOffset;
	std::string battleBehavior;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
};
