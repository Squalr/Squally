#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewEndianForest : public HexusChapterPreview
{
public:
	static HexusChapterPreviewEndianForest* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewEndianForest();
	~HexusChapterPreviewEndianForest();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
