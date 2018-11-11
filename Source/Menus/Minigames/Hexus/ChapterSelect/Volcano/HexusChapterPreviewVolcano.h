#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"
#include "Resources.h"

using namespace cocos2d;

class HexusChapterPreviewVolcano : public HexusChapterPreview
{
public:
	static HexusChapterPreviewVolcano * create();

	static const std::string stringKeyChapterName;

protected:
	HexusChapterPreviewVolcano();
	~HexusChapterPreviewVolcano();

private:
	void initializePositions() override;
};
