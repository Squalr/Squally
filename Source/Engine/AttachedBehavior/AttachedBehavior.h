
#pragma once

#include "Engine/Hackables/HackableObject.h"

class AttachedBehavior : public HackableObject
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
	typedef HackableObject super;
	
	void updateState();

	GameObject* owner;
	bool invalidated;
	bool queryable;
};

