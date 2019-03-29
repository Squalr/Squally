#pragma once
#include <string>
#include <vector>

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class CipherLevelItem;
class LocalizedLabel;
class ClickableNode;

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

	int currentPage;

	cocos2d::Sprite* tutorialWindow;
	LocalizedLabel* titleLabel;
	cocos2d::Sprite* descriptionBox;
	LocalizedLabel* description;
	ClickableNode* closeButton;

	cocos2d::ParticleSystem* nether;
	cocos2d::ParticleSystem* swirl;

	std::vector<CipherLevelItem*> hexusOpponentItems;

	static CipherSelectMenu* instance;
	static const cocos2d::Color3B TitleColor;
};
