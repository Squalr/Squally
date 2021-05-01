
#pragma once

#include "Engine/SmartNode.h"

class GameObject;

class Component : public SmartNode
{
public:
	bool isInvalidated();
	bool isQueryable();
	GameObject* getOwner();
	
	virtual void onDisable();

protected:
	Component(GameObject* owner);
	virtual ~Component();

	void onEnterTransitionDidFinish() override;

	virtual void onLoad() = 0;
	void invalidate();
	void toggleQueryable(bool queryable);
	
	GameObject* owner;

private:
	typedef SmartNode super;

	bool invalidated;
	bool queryable;
};

