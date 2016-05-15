#include "LSystem.h"
typedef std::map<char, std::string>::iterator iter;

LSytem::LSytem()
{
}

void LSytem::AddAxiom(char key, std::string rule)
{
	axioms[key] = rule;
}

std::string LSytem::ApplyAxioms(std:: string system)
{
	std::string applied = "";
	
	for (int c = 0; c < system.size(); c++)
	{
		bool passThrough = true;
		for (iter iterator = axioms.begin(); iterator != axioms.end(); iterator++)
		{
			if (system[c] == iterator->first)
			{
				passThrough = false;
				applied += iterator->second;
				break;
			}
		}
		if (passThrough)
			applied += system[c];
	}

	return applied;
}

std::string LSytem::ApplyAxioms(std::string system, int iterations)
{
	if (iterations <= 0)
		return system;
	std::string applied = system;
	for (int i = 0; i < iterations; i++)
	{
		applied = ApplyAxioms(applied);
	}

	return applied;
}
