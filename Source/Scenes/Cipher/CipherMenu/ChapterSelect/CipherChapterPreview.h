#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CipherPuzzleData;
class ClickableNode;

class CipherChapterPreview : public SmartNode
{
public:
	static CipherChapterPreview* create(std::string saveKey, std::string spriteResource, std::string spriteSelectedResource, std::string spriteDisabledResource);

	void setClickCallback(std::function<void()> callback);
	CipherPuzzleData* getPuzzleData();
	std::string getSaveKey();
	bool isChapterCleared();
	void enableInteraction();
	void disableInteraction();
	
private:
	typedef SmartNode super;
	CipherChapterPreview(std::string saveKey, std::string spriteResource, std::string spriteSelectedResource, std::string spriteDisabledResource);
	~CipherChapterPreview();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	std::string saveKey;
	CipherPuzzleData* cipherPuzzleData;
	ClickableNode* previewNode;
	cocos2d::Sprite* previewNodeDisabled;
};
