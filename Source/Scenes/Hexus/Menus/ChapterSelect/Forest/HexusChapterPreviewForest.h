#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewForest : public HexusChapterPreview
{
public:
	static HexusChapterPreviewForest* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewForest();
	~HexusChapterPreviewForest();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
