#include "GameComponentGroup.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

GameComponentGroup::GameComponentGroup(GameObject* owner, std::vector<GameComponent*> component) : super(owner)
{
	for (auto next : component)
	{
		owner->attachComponent(next);
	}
}

GameComponentGroup::~GameComponentGroup()
{
}
