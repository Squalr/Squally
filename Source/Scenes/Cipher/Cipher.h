#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;

class Cipher : public SmartNode
{
public:
	static Cipher* create();

	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	Cipher();
	~Cipher();

private:
	typedef SmartNode super;
	
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMenuExit();

	std::function<void()> backClickCallback;

	cocos2d::Node* leftPanel;
	cocos2d::Node* rightPanel;
	cocos2d::Sprite* cipherWindow;
	cocos2d::Sprite* cipherLabel;

	LocalizedLabel* cipherToolsLabel;
	ClickableTextNode* quitButton;

	LocalizedLabel* inputsLabel;
	LocalizedLabel* outputsLabel;
	ClickableTextNode* executeButton;
	ClickableNode* toggleButtonBin;
	ClickableNode* toggleButtonDec;
	ClickableNode* toggleButtonHex;
	ClickableNode* toggleButtonAscii;
	ClickableNode* viewAsciiTableButton;

	static const cocos2d::Color3B TitleColor;
};
