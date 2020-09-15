#pragma once

#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"

class Portal;

class BinderPortal : public MiniMapObjectBinder
{
public:
	static BinderPortal* create();

	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject) override;

protected:
	BinderPortal();
	virtual ~BinderPortal();

	void update(float dt) override;

private:
	typedef MiniMapObjectBinder super;

	Portal* portal;
};
