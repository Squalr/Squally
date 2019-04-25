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

class CipherChapterSelectMenu : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	CipherChapterSelectMenu();
	~CipherChapterSelectMenu();

private:
	typedef GlobalScene super;
	void loadLevels();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onCloseClick();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	cocos2d::ParticleSystem* nether;
	cocos2d::ParticleSystem* swirl;
	
	LocalizedLabel* titleLabel;
	ClickableNode* backButton;

	ClickableNode* chapterEndianForest;
	ClickableNode* chapterUnderflowRuins;
	ClickableNode* chapterSeaSharpCaverns;
	ClickableNode* chapterCastleValgrind;
	ClickableNode* chapterBalmerPeaks;
	ClickableNode* chapterDaemonsHallow;
	ClickableNode* chapterLambdaCrypts;
	ClickableNode* chapterVoidStar;

	std::vector<ClickableNode*> chapters;

	static CipherChapterSelectMenu* instance;
	static const cocos2d::Color3B TitleColor;
};
