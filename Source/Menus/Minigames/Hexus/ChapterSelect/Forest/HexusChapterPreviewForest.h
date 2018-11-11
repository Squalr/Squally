#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"
#include "Resources.h"

using namespace cocos2d;

class HexusChapterPreviewForest : public HexusChapterPreview
{
public:
	static HexusChapterPreviewForest * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewForest();
	~HexusChapterPreviewForest();

private:
	void initializePositions() override;
};
