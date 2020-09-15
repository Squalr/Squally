#pragma once

#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"

class MechanicalFlail;

class BinderMechanicalFlail : public MiniMapObjectBinder
{
public:
	static BinderMechanicalFlail* create();

	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject) override;

protected:
	BinderMechanicalFlail();
	virtual ~BinderMechanicalFlail();

	void update(float dt) override;

private:
	typedef MiniMapObjectBinder super;

	MechanicalFlail* mechanicalFlail;
};
