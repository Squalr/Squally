#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewTraining : public HexusChapterPreview
{
public:
	static HexusChapterPreviewTraining * create();

protected:
	HexusChapterPreviewTraining();
	~HexusChapterPreviewTraining();

private:
	void initializePositions() override;
};
