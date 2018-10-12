#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Mermaid : public PlatformerEnemy
{
public:
	static Mermaid * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMermaid;

private:
	Mermaid(ValueMap* initProperties);
	~Mermaid();
};
