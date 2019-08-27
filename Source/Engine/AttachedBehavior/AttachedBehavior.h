
#pragma once

#include "Engine/Hackables/HackableObject.h"

class AttachedBehavior : public HackableObject
{
public:
	bool isInvalidated();

protected:
	AttachedBehavior(GameObject* owner);
	~AttachedBehavior();

	void initializeListeners() override;
	void onEnterTransitionDidFinish() override;

	virtual void onLoad() = 0;
	void invalidate();

private:
	typedef HackableObject super;
	
	void updateState();

	GameObject* owner;
	bool invalidated;
};

