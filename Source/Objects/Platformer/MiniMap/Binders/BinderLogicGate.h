#pragma once

#include "Objects/Platformer/MiniMap/Binders/MiniMapObjectBinder.h"

class LogicGate;

class BinderLogicGate : public MiniMapObjectBinder
{
public:
	static BinderLogicGate* create();

	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject) override;

protected:
	BinderLogicGate();
	virtual ~BinderLogicGate();

	void update(float dt) override;

private:
	typedef MiniMapObjectBinder super;

	LogicGate* logicGate;
};
