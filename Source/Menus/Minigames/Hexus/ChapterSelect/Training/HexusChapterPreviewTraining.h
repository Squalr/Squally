#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

using namespace cocos2d;

class HexusChapterPreviewTraining : public HexusChapterPreview
{
public:
	static HexusChapterPreviewTraining * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewTraining();
	~HexusChapterPreviewTraining();

private:
	void initializePositions() override;
};
