#pragma once
#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;

class GameObject : public Node
{
public:
	GameObject();
	~GameObject();

protected:
	virtual void onEnter() override;
	virtual void initializePositions();
	virtual void initializeListeners();
};

