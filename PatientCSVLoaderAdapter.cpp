#include "PatientCSVLoaderAdapter.h"
#include "Utility.h"

void PatientCSVLoaderAdapter::initialiseConnection()
{
	if (!_csvLoader.openFile())
	{
		strtk001Utils::logError("cannot initalise connection");
	}
}

void PatientCSVLoaderAdapter::loadPatients(std::vector<Patient*>& patientIn)
{
	_csvLoader.loadPatientsFromCSV(patientIn);
}

void PatientCSVLoaderAdapter::closeConnection()
{
	if (!_csvLoader.closeFile())
	{
		strtk001Utils::logError("failed to close connection");
	}
}