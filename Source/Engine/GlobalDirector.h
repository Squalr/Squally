#pragma once
#include <stack>

#include "Engine/GlobalNode.h"

class GlobalHud;
class GlobalScene;
class SmartScene;

class GlobalDirector : public GlobalNode
{
public:
	static GlobalDirector* getInstance();

	static void loadScene(std::function<SmartScene*()> sceneCreator);
	static void RegisterGlobalNode(GlobalNode* node);
	static void RegisterGlobalNode(GlobalHud* node);
	static void RegisterGlobalScene(GlobalScene* node);

	template <class T>
	std::vector<T*> getGlobalNodesOfType()
	{
		std::vector<T*> instances;
		for (SmartNode* node : globalNodes)
		{
			if (dynamic_cast<T*>(node) != nullptr)
			{
				instances.push_back(dynamic_cast<T*>(node));
			}
		}

		return instances;
	}

protected:
	GlobalDirector();
	virtual ~GlobalDirector();

	SmartScene* activeScene = nullptr;
	std::vector<SmartNode*> globalNodes;
	std::vector<GlobalScene*> globalScenes;

	static GlobalDirector* Instance;
private:
	typedef GlobalNode super;
};
