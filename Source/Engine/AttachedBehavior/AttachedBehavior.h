
#pragma once

#include "Engine/SmartNode.h"

class GameObject;

class AttachedBehavior : public SmartNode
{
public:
	bool isInvalidated();
	bool isQueryable();

	virtual void onDisable();

protected:
	AttachedBehavior(GameObject* owner);
	virtual ~AttachedBehavior();

	void onEnterTransitionDidFinish() override;

	virtual void onLoad() = 0;
	void invalidate();
	void toggleQueryable(bool queryable);

private:
	typedef SmartNode super;
	
	void updateState();

	GameObject* owner;
	bool invalidated;
	bool queryable;
};

