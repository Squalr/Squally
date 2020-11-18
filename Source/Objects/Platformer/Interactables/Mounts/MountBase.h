#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

class PlatformerEntity;

class MountBase : public InteractObject
{
public:
	cocos2d::Node* getReparentNode();

	virtual void mount(PlatformerEntity* interactingEntity);
	virtual void dismount();

protected:
	MountBase(cocos2d::ValueMap& properties, cocos2d::Size size);
	virtual ~MountBase();

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onInteract(PlatformerEntity* interactingEntity) override;
	virtual cocos2d::Vec2 getReparentPosition();
	
	void setToMountPositionX();
	void setToMountPosition();
	
	cocos2d::Node* backNode;
	cocos2d::Node* frontNode;
	PlatformerEntity* mountedEntity;

private:
	typedef InteractObject super;

	cocos2d::Node* reparentNode;
};
