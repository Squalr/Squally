#pragma once
#include "cocos2d.h"

#include "Engine/GlobalNode.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class GlobalDirector : public Node
{
public:
	static GlobalDirector* getInstance();

	void loadScene(Scene* scene);
	void registerGlobalNode(GlobalNode* node);

protected:
	GlobalDirector();
	~GlobalDirector();

	Scene* activeScene;
	std::vector<GlobalNode*>* globalNodes;

	static GlobalDirector* instance;
};
