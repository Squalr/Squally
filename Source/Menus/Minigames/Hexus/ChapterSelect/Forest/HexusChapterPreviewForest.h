#pragma once
#include <string>

#include "Menus/Minigames/Hexus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewForest : public HexusChapterPreview
{
public:
	static HexusChapterPreviewForest* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewForest();
	~HexusChapterPreviewForest();

private:
	void initializePositions() override;
};
