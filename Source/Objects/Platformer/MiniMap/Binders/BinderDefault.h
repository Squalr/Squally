#pragma once

#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"

class BinderDefault : public MiniMapObjectBinder
{
public:
	static BinderDefault* create();

	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject) override;

protected:
	BinderDefault();
	virtual ~BinderDefault();

	void update(float dt) override;

private:
	typedef MiniMapObjectBinder super;
};
