#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Node;
}

class OptionsMenu;

class OptionsScene : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	OptionsScene();
	~OptionsScene();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* backgroundNode;
	OptionsMenu* menu;

	static OptionsScene* instance;
};

