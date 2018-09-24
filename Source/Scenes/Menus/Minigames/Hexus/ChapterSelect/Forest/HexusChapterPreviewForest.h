#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewForest : public HexusChapterPreview
{
public:
	static HexusChapterPreviewForest * create();

protected:
	HexusChapterPreviewForest();
	~HexusChapterPreviewForest();

private:
	void initializePositions() override;
};
