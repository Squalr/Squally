
#pragma once

#include "Engine/SmartNode.h"

class GameObject;

class AttachedBehavior : public SmartNode
{
public:
	bool isInvalidated();
	bool isQueryable();
	GameObject* getOwner();
	
	virtual void onDisable();

protected:
	AttachedBehavior(GameObject* owner);
	virtual ~AttachedBehavior();

	void onEnterTransitionDidFinish() override;

	virtual void onLoad() = 0;
	void invalidate();
	void toggleQueryable(bool queryable);
	
	GameObject* owner;

private:
	typedef SmartNode super;
	
	void updateState();

	bool invalidated;
	bool queryable;
};

