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

	std::function<void()> backClickCallback = nullptr;

	cocos2d::Node* background = nullptr;
	cocos2d::Sprite* optionsWindow = nullptr;
	LocalizedLabel* optionsLabel = nullptr;
	ClickableNode* closeButton = nullptr;
	ClickableTextNode* cancelButton = nullptr;
	ClickableTextNode* returnButton = nullptr;
	cocos2d::Node* leftPanel = nullptr;
	ClickableTextNode* generalTabButton = nullptr;
	ClickableTextNode* videoTabButton = nullptr;
	ClickableTextNode* languageTabButton = nullptr;
	ClickableTextNode* memesTabButton = nullptr;
	cocos2d::Node* rightPanel = nullptr;
	GeneralTab* generalTab = nullptr;
	VideoTab* videoTab = nullptr;
	LanguageTab* languageTab = nullptr;
	MemesTab* memesTab = nullptr;

	Tab activeTab = Tab::General;

	bool useEnterFade = false;

	static const cocos2d::Color3B TitleColor;
};
