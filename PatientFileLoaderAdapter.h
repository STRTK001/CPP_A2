#ifndef PATIENTFILELOADERADAPTER_H
#define PATIENTFILELOADERADAPTER_H

#include "AbstractPatientDatabaseLoader.h"
#include "PatientFileLoader.h"

class PatientFileLoaderAdapter : public AbstractPatientDatabaseLoader
{
public:
	PatientFileLoaderAdapter(const std::string& filePath) : _fileLoader(filePath) {}
	void initialiseConnection() override;
	void loadPatients(std::vector<Patient*>& patientIn) override;
	void closeConnection() override;
private:
	PatientFileLoader _fileLoader;
};

#endif