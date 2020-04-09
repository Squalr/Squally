#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class MageCastBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
