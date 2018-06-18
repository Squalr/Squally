#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Mermaid : public Enemy
{
public:
	static Mermaid * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMermaid;

private:
	Mermaid(ValueMap* initProperties);
	~Mermaid();
};
