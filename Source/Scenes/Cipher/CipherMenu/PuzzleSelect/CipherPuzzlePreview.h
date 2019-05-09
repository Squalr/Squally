#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CipherPuzzleData;
class ClickableNode;

class CipherPuzzlePreview : public SmartNode
{
public:
	static CipherPuzzlePreview* create(CipherPuzzleData* cipherPuzzleData, std::string spriteResource, std::string spriteSelectedResource, std::string spriteDisabledResource);

	void enableInteraction();
	void disableInteraction();
	CipherPuzzleData* getPuzzleData();
	
private:
	typedef SmartNode super;
	CipherPuzzlePreview(CipherPuzzleData* cipherPuzzleData, std::string spriteResource, std::string spriteSelectedResource, std::string spriteDisabledResource);
	~CipherPuzzlePreview();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	CipherPuzzleData* cipherPuzzleData;
	ClickableNode* previewNode;
	cocos2d::Sprite* previewNodeDisabled;
};
