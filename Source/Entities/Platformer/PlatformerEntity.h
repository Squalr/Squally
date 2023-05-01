#pragma once

#include "Engine/Hackables/HackableObject.h"

class HackablePreview;
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

	float getScale();
	std::string getAnimationResource();
	std::string getEmblemResource();
	cocos2d::Node* getFloatNode();
	SmartAnimationNode* getAnimations();
	cocos2d::CSize getEntitySize();
	cocos2d::Vec2 getEntityCenterPoint();
	cocos2d::Vec2 getEntityTopPoint();
	cocos2d::Vec2 getEntityBottomPoint();
	cocos2d::Vec2 getEntityTopPointRelative();
	cocos2d::Vec2 getEntityBottomPointRelative();
	float getHoverHeight();
	virtual cocos2d::Vec2 getDialogueOffset() = 0;
	virtual LocalizedString* getEntityName() = 0;
	virtual std::string getSwimAnimation();
	virtual std::string getJumpAnimation();
	virtual std::string getJumpSound();
	virtual std::vector<std::string> getSwimSounds();
	virtual std::vector<std::string> getWalkSounds();
	PlatformerEntity::ControlState getControlState();
	bool isFlippedX();
	bool isFlippedY();
	PlatformerEntity* uiClone();
	std::string getBattleBehavior();

	ControlState controlState;
	ControlState controlStateOverride;

	static const std::string PlatformerEntityTag;
	static const std::string PropertyBattleBehavior;

protected:
	PlatformerEntity(
		cocos2d::ValueMap& properties,
		std::string entityName,
		std::string scmlResource,
		std::string emblemResource,
		cocos2d::CSize size,
		float scale,
		float hoverHeight = 0.0f);
	virtual ~PlatformerEntity();
	
	void onEnter() override;
	void update(float dt) override;
	cocos2d::Vec2 getRainOffset() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;

	std::string state;

	cocos2d::Node* floatNode = nullptr;
	cocos2d::Node* belowAnimationNode = nullptr;
	SmartAnimationNode* animationNode = nullptr;

	static const std::string PropertyState;

private:
	typedef HackableObject super;

	void optimizationHideOffscreenEntity();
	
	float entityScale = 1.0f;
	cocos2d::CSize entitySize;
	float hoverHeight = 0.0f;
	std::string entityName;
	std::string animationResource;
	std::string emblemResource;
	cocos2d::Vec2 hackButtonOffset;
	std::string battleBehavior;
	PlatformerEntityDeserializer* platformerEntityDeserializer = nullptr;
};
