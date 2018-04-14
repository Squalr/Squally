#ifndef VARIABLECONTAINER_H
#define VARIABLECONTAINER_H

#include <vector>

#include "../global/global.h"

#include "variable.h"

namespace SpriterEngine
{

	class VariableInstanceNameAndIdMap;

	typedef std::vector<Variable*> VariableVector;

	class VariableContainer
	{
	public:
		VariableContainer();
		virtual ~VariableContainer();

		Variable *getVariable(int variableIndex);

		void addStringVariable(std::string variableName, std::string defaultValue);
		void addIntVariable(std::string variableName, int defaultValue);
		void addRealVariable(std::string variableName, real defaultValue);

		void setupVariableInstances(VariableInstanceNameAndIdMap *variableMap);

		void setupDefaultVariableTimelines(Animation * animation, int objectId);

	private:
		VariableVector variables;
	};

}

#endif // ENTITY_H