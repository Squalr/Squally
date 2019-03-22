#pragma once

#include "Scenes/Cipher/Components/Blocks/Connections/BoltBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class InputBolt : public BoltBase
{
public:
	static InputBolt* create();

	void setConnection(Connection* connection) override;
	void hideHelp();

private:
	typedef BoltBase super;
	InputBolt();
	~InputBolt();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* bolt;
	cocos2d::Sprite* helperArrow;
};
