#pragma once
#include <tuple>

#include "Engine/SmartNode.h"

class 
CipherPuzzleData : public SmartNode
{
public:
	static CipherPuzzleData* create(
		std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMap,
		std::vector<std::string> tokens,
		std::string defaultDataType,
		std::string tutorial,
		std::function<void(CipherPuzzleData*)> onUnlock);
	
	CipherPuzzleData* clone();
	std::vector<std::tuple<unsigned char, unsigned char>> getInputOutputMap();
	std::vector<std::string> getTokens();
	std::string getDefaultDataType();
	std::string getTutorial();
	std::function<void(CipherPuzzleData*)> onUnlock;

protected:
	CipherPuzzleData(std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMap,
		std::vector<std::string> tokens,
		std::string defaultDataType,
		std::string tutorial,
		std::function<void(CipherPuzzleData*)> onUnlock);
	virtual ~CipherPuzzleData();

	void initializeListeners() override;

private:
	typedef SmartNode super;

	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMap;
	std::string defaultDataType;
	std::vector<std::string> tokens;
	std::string tutorial;
};
