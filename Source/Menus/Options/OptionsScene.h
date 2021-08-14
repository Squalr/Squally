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
	static OptionsScene* getInstance();

protected:
	OptionsScene();
	virtual ~OptionsScene();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GlobalScene super;

	cocos2d::Node* backgroundNode = nullptr;
	OptionsMenu* menu = nullptr;

	static OptionsScene* instance;
};

