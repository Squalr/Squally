#pragma once

#include "Engine/Hackables/HackableObject.h"

class AttachedBehavior : public HackableObject
{
public:
	std::string getAttachedBehaviorArgs();

protected:
	AttachedBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~AttachedBehavior();

	void initializeListeners() override;
	void onEnterTransitionDidFinish() override;

	virtual void onLoad() = 0;
	void invalidate();

private:
	typedef HackableObject super;
	
	void updateState();

	GameObject* owner;
	std::string attachedBehaviorArgs;
	bool isInvalidated;
};

