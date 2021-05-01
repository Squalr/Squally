#pragma once

#include "Engine/Components/Component.h"

namespace cocos2d
{
	class Sprite;
}

class InteractObject;
class Inventory;
class PlatformerEntity;
class SmartParticles;
class WorldSound;

class EntityPetrificationBehavior : public Component
{
public:
	static EntityPetrificationBehavior* create(GameObject* owner);

	bool isCured();
	void unpetrify();
	void runDialogue();

	static const std::string MapKey;
	static const std::string MapEventCured;
	static const std::string MapEventKeyOwnerId;

protected:
	EntityPetrificationBehavior(GameObject* owner);
	virtual ~EntityPetrificationBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	bool tryCure();
	void ajaxRun();

	PlatformerEntity* entity;
	InteractObject* cureInteraction;
	cocos2d::Vec2 displayOffset;
	Inventory* inventory;
	SmartParticles* unpetrifyParticles;
	WorldSound* statueBreakSound;
	
	cocos2d::Node* rotationNode;
	cocos2d::Sprite* petrifiedSprite;

	static const std::string SaveKeyCured;
	static const std::string TagExit;
};
