#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;

class EntitySelectionOverlayBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	cocos2d::Sprite* lightRay = nullptr;
};
