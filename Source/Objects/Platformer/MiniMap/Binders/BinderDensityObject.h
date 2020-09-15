#pragma once

#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"

class DensityObject;

class BinderDensityObject : public MiniMapObjectBinder
{
public:
	static BinderDensityObject* create();

	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject) override;

protected:
	BinderDensityObject();
	virtual ~BinderDensityObject();

	void update(float dt) override;

private:
	typedef MiniMapObjectBinder super;

	DensityObject* densityObject;
};
