#pragma once

#include "Engine/Components/Component.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;

class EntitySelectionOverlayBehavior : public Component
{
public:
	static EntitySelectionOverlayBehavior* create(GameObject* owner);

	void trySelect(PlatformerEntity* entity);

	static const std::string MapKey;

protected:
	EntitySelectionOverlayBehavior(GameObject* owner);
	virtual ~EntitySelectionOverlayBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	PlatformerEntity* entity;
	cocos2d::Sprite* lightRay;
};
