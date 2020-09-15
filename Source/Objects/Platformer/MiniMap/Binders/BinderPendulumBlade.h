#pragma once

#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"

class PendulumBlade;

class BinderPendulumBlade : public MiniMapObjectBinder
{
public:
	static BinderPendulumBlade* create();

	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject) override;

protected:
	BinderPendulumBlade();
	virtual ~BinderPendulumBlade();

	void update(float dt) override;

private:
	typedef MiniMapObjectBinder super;

	PendulumBlade* pendulumBlade;
};
