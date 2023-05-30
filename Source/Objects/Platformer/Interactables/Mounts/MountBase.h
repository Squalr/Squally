#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

class PlatformerEntity;

class MountBase : public InteractObject
{
public:
	enum class MountDirection
	{
		None,
		Left,
		Right
	};

	cocos2d::Node* getReparentNode();
	virtual void mount(PlatformerEntity* interactingEntity);
	virtual void dismount(PlatformerEntity* entity);
	void dismountAll();
	bool isMounted() const;
	bool isTargetMounted(PlatformerEntity* entity) const;
	void setMountDirection(MountDirection mountDirection);
	void reverse();
	void parseDirection();

protected:
	MountBase(cocos2d::ValueMap& properties, cocos2d::CSize size, bool updateXOnly = true);
	virtual ~MountBase();

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onInteract(PlatformerEntity* interactingEntity) override;
	virtual cocos2d::Vec2 getReparentPosition();
	
	void setToMountPositionX();
	void setToMountPosition();

	void faceEntityTowardsDirection();
	void moveMount(float dt);
	
	cocos2d::Node* rootNode = nullptr;
	cocos2d::Node* frontNode = nullptr;
	std::set<PlatformerEntity*> mountedEntities;
	MountDirection mountDirection = MountDirection::Left;
	float mountSpeed = 0.0f;
	bool isMoving = false;
	volatile bool canMoveOverride = true;
	bool updateXOnly = true;

	static const std::string PropertyDirection;
	static const std::string PropertySpeed;

private:
	typedef InteractObject super;

	cocos2d::Node* reparentNode = nullptr;
};
