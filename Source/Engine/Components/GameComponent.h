
#pragma once

#include "Engine/SmartNode.h"

class GameObject;

class GameComponent : public SmartNode
{
public:
	bool isInvalidated();
	bool isQueryable();
	GameObject* getOwner();
	
	virtual void onDisable();

protected:
	GameComponent(GameObject* owner);
	virtual ~GameComponent();

	void onEnterTransitionDidFinish() override;

	virtual void onLoad() = 0;
	void invalidate();
	void toggleQueryable(bool queryable);
	
	GameObject* owner = nullptr;

private:
	typedef SmartNode super;

	bool invalidated = false;
	bool queryable = true;
};

