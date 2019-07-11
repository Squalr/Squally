#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class ParticleSystem;
	class Sprite;
}

class LocalizedLabel;
class CipherPuzzlePreview;
class ClickableNode;
class ScrollPane;
class ClickableTextNode;

class CipherPuzzleSelectMenuBase : public GlobalScene
{
protected:
	CipherPuzzleSelectMenuBase(std::string chapterProgressSaveKey);
	~CipherPuzzleSelectMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick();
	void buildCipherList();
	static std::string buildCipherJson(std::string rule, std::vector<std::string> inputs);

	std::vector<CipherPuzzlePreview*> chests;
	std::map<CipherPuzzlePreview*, CipherPuzzlePreview*> dependencies;

	std::string chapterProgressSaveKey;
	cocos2d::ParticleSystem* nether;
	cocos2d::ParticleSystem* swirl;
	cocos2d::Sprite* backboard;
	ClickableTextNode* backButton;
	
private:
	typedef GlobalScene super;
};
