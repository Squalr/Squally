#pragma once
#include <string>
#include <vector>

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class CipherChapterPreview;
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
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadLevels();
	void onCloseClick();

	cocos2d::ParticleSystem* nether;
	cocos2d::ParticleSystem* swirl;
	
	cocos2d::Sprite* backboard;
	CipherChapterPreview* chapterEndianForest;
	CipherChapterPreview* chapterUnderflowRuins;
	CipherChapterPreview* chapterSeaSharpCaverns;
	CipherChapterPreview* chapterCastleValgrind;
	CipherChapterPreview* chapterBalmerPeaks;
	CipherChapterPreview* chapterDaemonsHallow;
	CipherChapterPreview* chapterLambdaCrypts;
	CipherChapterPreview* chapterVoidStar;
	LocalizedLabel* titleLabel;
	ClickableNode* backButton;

	std::vector<CipherChapterPreview*> chapters;

	static CipherChapterSelectMenu* instance;
	static const cocos2d::Color3B TitleColor;
};
