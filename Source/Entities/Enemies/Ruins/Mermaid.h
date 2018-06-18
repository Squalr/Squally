#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Mermaid : public Enemy
{
public:
	static Mermaid * create();

	static const std::string KeyEnemyMermaid;

private:
	Mermaid();
	~Mermaid();
};
