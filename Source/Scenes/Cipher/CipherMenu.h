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

class CipherMenu : public SmartNode
{
public:
	static CipherMenu* create();

	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	CipherMenu();
	~CipherMenu();

private:
	typedef SmartNode super;
	
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMenuCancel();
	void onMenuExit();

	std::function<void()> backClickCallback;

	cocos2d::Node* background;
	cocos2d::Sprite* cipherWindow;
	cocos2d::Sprite* cipherToolsWindow;
	LocalizedLabel* cipherLabel;
	cocos2d::Sprite* cipherLabelRendered;
	LocalizedLabel* cipherToolsLabel;
	ClickableNode* closeButton;
	ClickableTextNode* cancelButton;
	ClickableTextNode* returnButton;
	cocos2d::Node* leftPanel;
	cocos2d::Node* rightPanel;

	static const cocos2d::Color3B TitleColor;
};
