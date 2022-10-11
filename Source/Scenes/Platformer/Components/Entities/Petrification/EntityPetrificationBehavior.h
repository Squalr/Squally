#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class InteractObject;
class Inventory;
class PlatformerEntity;
class SmartParticles;
class WorldSound;

class EntityPetrificationBehavior : public GameComponent
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
	typedef GameComponent super;

	bool tryCure();
	void ajaxRun();

	PlatformerEntity* entity = nullptr;
	InteractObject* cureInteraction = nullptr;
	cocos2d::Vec2 displayOffset;
	Inventory* inventory = nullptr;
	SmartParticles* unpetrifyParticles = nullptr;
	WorldSound* statueBreakSound = nullptr;
	cocos2d::Node* rotationNode = nullptr;
	cocos2d::Sprite* petrifiedSprite = nullptr;

	static const std::string SaveKeyCured;
	static const std::string TagExit;
};
