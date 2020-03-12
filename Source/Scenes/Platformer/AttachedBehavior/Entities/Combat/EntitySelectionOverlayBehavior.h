#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;

class EntitySelectionOverlayBehavior : public AttachedBehavior
{
public:
	static EntitySelectionOverlayBehavior* create(GameObject* owner);

	void trySelect(PlatformerEntity* entity);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntitySelectionOverlayBehavior(GameObject* owner);
	virtual ~EntitySelectionOverlayBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	cocos2d::Sprite* lightRay;
};
