
#pragma once

#include "Engine/Hackables/HackableObject.h"

class AttachedBehavior : public HackableObject
{
public:
	bool isInvalidated();
	bool isQueryable();

protected:
	AttachedBehavior(GameObject* owner);
	virtual ~AttachedBehavior();

	void initializeListeners() override;
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

