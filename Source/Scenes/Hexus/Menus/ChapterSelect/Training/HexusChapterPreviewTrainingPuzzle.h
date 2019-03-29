#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewTrainingPuzzle : public HexusChapterPreview
{
public:
	static HexusChapterPreviewTrainingPuzzle * create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewTrainingPuzzle();
	~HexusChapterPreviewTrainingPuzzle();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
