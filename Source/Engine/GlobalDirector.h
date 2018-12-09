#pragma once
#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Scene;
}

class GlobalDirector : public GlobalNode
{
public:
	static GlobalDirector* getInstance();

	void loadScene(cocos2d::Scene* scene);
	void registerGlobalNode(GlobalNode* node);

protected:
	GlobalDirector();
	virtual ~GlobalDirector();

	cocos2d::Scene* activeScene;
	std::vector<GlobalNode*> globalNodes;

	static GlobalDirector* instance;
};
