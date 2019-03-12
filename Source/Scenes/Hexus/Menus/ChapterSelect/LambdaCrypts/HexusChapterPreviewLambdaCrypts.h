#pragma once

#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterPreview.h"

class HexusChapterPreviewLambdaCrypts : public HexusChapterPreview
{
public:
	static HexusChapterPreviewLambdaCrypts* create();

	static const std::string SaveKeyChapterName;

protected:
	HexusChapterPreviewLambdaCrypts();
	~HexusChapterPreviewLambdaCrypts();

private:
	typedef HexusChapterPreview super;
	void initializePositions() override;
};
