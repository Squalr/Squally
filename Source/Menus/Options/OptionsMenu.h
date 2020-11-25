#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class GeneralTab;
class LanguageTab;
class LocalizedLabel;
class LocalizedString;
class MemesTab;
class VideoTab;

class OptionsMenu : public SmartNode
{
public:
	static OptionsMenu* create(bool useEnterFade);

	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	OptionsMenu(bool useEnterFade);
	virtual ~OptionsMenu();
	
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	enum class Tab
	{
		General,
		Video,
		Language,
		Memes,
	};

	void setActiveTab(Tab tab);
	void onMenuCancel();
	void onMenuExit();
	ClickableTextNode* buildTabButton(std::string iconResource, LocalizedString* localizedString);

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
	ClickableTextNode* memesTabButton;
	cocos2d::Node* rightPanel;
	GeneralTab* generalTab;
	VideoTab* videoTab;
	LanguageTab* languageTab;
	MemesTab* memesTab;

	Tab activeTab;

	bool useEnterFade;

	static const cocos2d::Color3B TitleColor;
};
