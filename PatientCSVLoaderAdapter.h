#ifndef PATIENTCSVLOADERADAPTER_H
#define PATIENTCSVLOADERADAPTER_H

#include "AbstractPatientDatabaseLoader.h"
#include "PatientCSVLoader.h"

class PatientCSVLoaderAdapter : public AbstractPatientDatabaseLoader
{
public:
	PatientCSVLoaderAdapter(const std::string& filePath) : _csvLoader(filePath) {}
	void initialiseConnection() override;
	void loadPatients(std::vector<Patient*>& patientIn) override;
	void closeConnection() override;
private:
	PatientCSVLoader _csvLoader;
};

#endif