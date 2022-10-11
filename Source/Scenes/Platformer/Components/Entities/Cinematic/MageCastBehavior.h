#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class MageCastBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
