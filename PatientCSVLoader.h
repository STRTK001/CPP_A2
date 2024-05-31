#ifndef PATIENTCSVLOADER_H
#define PATIENTCSVLOADER_H

#include "Patient.h"
#include "Vitals.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

class PatientCSVLoader
{
public:
	PatientCSVLoader(const std::string& filepath) : _filePath(filepath) {}

	void loadPatientsFromCSV(std::vector<Patient*>& patientIn);
	bool openFile();
	bool closeFile();

private:
	std::ifstream _databaseFile;
	std::string _filePath;

	std::vector<std::string> splitString(const std::string& str, char delimiter);
};
#endif
