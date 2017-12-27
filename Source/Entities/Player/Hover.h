#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Input/InputManager.h"

using namespace cocos2d;

class Hover : public Entity
{
public:
	static Hover * create();

private:
	Hover();
	~Hover();
};

