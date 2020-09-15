#pragma once

#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"

class TrapDoor;

class BinderTrapDoor : public MiniMapObjectBinder
{
public:
	static BinderTrapDoor* create();

	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject) override;

protected:
	BinderTrapDoor();
	virtual ~BinderTrapDoor();

	void update(float dt) override;

private:
	typedef MiniMapObjectBinder super;

	TrapDoor* trapDoor;
};
