#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class Item;
class MinMaxPool;
class RecipePoolDeserializer;
class SmartAnimationSequenceNode;
class WorldSound;

class MountBase : public InteractObject
{
public:
	cocos2d::Node* getReparentNode();
	virtual cocos2d::Vec2 getReparentPosition();

protected:
	MountBase(cocos2d::ValueMap& properties, cocos2d::Size size);
	virtual ~MountBase();

	void onInteract(PlatformerEntity* interactingEntity) override;
	virtual void mount(PlatformerEntity* interactingEntity);
	virtual void dismount();
	
	cocos2d::Node* backNode;
	cocos2d::Node* frontNode;

private:
	typedef InteractObject super;

	PlatformerEntity* mountedEntity;
	cocos2d::Node* reparentNode;
};
