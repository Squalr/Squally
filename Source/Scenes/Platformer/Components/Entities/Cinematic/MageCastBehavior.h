#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class MageCastBehavior : public Component
{
public:
	static MageCastBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MageCastBehavior(GameObject* owner);
	virtual ~MageCastBehavior();
	
	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	PlatformerEntity* entity;
};
