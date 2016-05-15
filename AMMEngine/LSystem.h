#pragma once
#include <iostream>
#include <map>

class LSytem {
public:
	LSytem();
	std::map<char, std::string> axioms;

	void AddAxiom(char key, std::string rule);

	std::string ApplyAxioms(std::string system);

	std::string ApplyAxioms(std::string system, int iterations);
};