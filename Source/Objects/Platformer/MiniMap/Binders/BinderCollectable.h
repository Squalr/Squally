#pragma once

#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"

class Collectable;

class BinderCollectable : public MiniMapObjectBinder
{
public:
	static BinderCollectable* create();

	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject) override;

protected:
	BinderCollectable();
	virtual ~BinderCollectable();

	void update(float dt) override;

private:
	typedef MiniMapObjectBinder super;

	Collectable* collectable;
};
