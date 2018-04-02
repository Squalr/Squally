#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Mermaid : public Enemy
{
public:
	static Mermaid * create();

private:
	Mermaid();
	~Mermaid();
};
