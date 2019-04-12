#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewEndianForestPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewEndianForestPuzzle* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewEndianForestPuzzle();
	~HexusChapterPreviewEndianForestPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
