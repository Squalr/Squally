#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SourceBlock : public BlockBase
{
public:
	static SourceBlock* create();
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	SourceBlock();
	~SourceBlock();

	void onEnter() override;
	void initializePositions() override;
};
