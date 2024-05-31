#include "PatientFileLoaderAdapter.h"
#include "Utility.h"

void PatientFileLoaderAdapter::initialiseConnection()
{
	//i guess we also pretend that we're connecting to a DB
}

void PatientFileLoaderAdapter::loadPatients(std::vector<Patient*>& patientIn)
{
	patientIn = _fileLoader.loadPatientFile();
}

void PatientFileLoaderAdapter::closeConnection()
{
	//i guess we also pretend that we're disconnecting from a DB
}