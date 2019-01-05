#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Node;
	class Sprite;
	class Label;
}

class GeneralTab;
class LanguageTab;
class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;
class VideoTab;

class OptionsMenu : public Hud
{
public:
	static OptionsMenu* create();

	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	OptionsMenu();
	~OptionsMenu();

private:
	typedef Hud super;

	enum class Tab
	{
		General,
		Video,
		Language,
	};

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void setActiveTab(Tab tab);
	void onMenuCancel();
	void onMenuExit();

	std::function<void()> backClickCallback;

	cocos2d::Node* background;
	cocos2d::Sprite* optionsWindow;
	LocalizedLabel* optionsLabel;
	ClickableNode* closeButton;
	ClickableTextNode* cancelButton;
	ClickableTextNode* returnButton;
	cocos2d::Node* leftPanel;
	ClickableTextNode* generalTabButton;
	ClickableTextNode* videoTabButton;
	ClickableTextNode* languageTabButton;
	cocos2d::Node* rightPanel;
	GeneralTab* generalTab;
	VideoTab* videoTab;
	LanguageTab* languageTab;

	Tab activeTab;

	static const cocos2d::Color3B TitleColor;
};
