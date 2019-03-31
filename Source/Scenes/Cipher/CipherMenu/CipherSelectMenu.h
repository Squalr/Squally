#pragma once
#include <string>
#include <vector>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class CipherLevelItem;
class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class LocalizedString;

class CipherSelectMenu : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	CipherSelectMenu();
	~CipherSelectMenu();

private:
	typedef GlobalScene super;
	void loadLevels();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onCloseClick();
	void onMouseOver(CipherLevelItem* tutorialItem);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	ClickableTextNode* buildTabButton(std::string iconResource, LocalizedString* localizedString);

	cocos2d::ParticleSystem* nether;
	cocos2d::ParticleSystem* swirl;

	cocos2d::Sprite* window;
	LocalizedLabel* titleLabel;
	cocos2d::Sprite* descriptionBox;
	LocalizedLabel* description;
	ClickableNode* closeButton;

	ClickableTextNode* tutorialsTabButton;
	ClickableTextNode* easyTabButton;
	ClickableTextNode* mediumTabButton;
	ClickableTextNode* hardTabButton;
	cocos2d::Node* leftPanel;
	cocos2d::Node* rightPanel;
	cocos2d::Node* tutorialsTab;
	cocos2d::Node* easyTab;
	cocos2d::Node* mediumTab;
	cocos2d::Node* hardTab;

	std::vector<CipherLevelItem*> hexusOpponentItems;

	static CipherSelectMenu* instance;
	static const cocos2d::Color3B TitleColor;
};
