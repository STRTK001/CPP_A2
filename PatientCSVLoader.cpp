#include "PatientCSVLoader.h"
#include "Utility.h"

void PatientCSVLoader::loadPatientsFromCSV(std::vector<Patient*>& patientIn)
{
	if (!_databaseFile.is_open())
	{
		//return as we dont have an open file
		strtk001Utils::logError("cannot load patients as the file isnt open");
		return;
	}
	//store an empty string to represent a line
	std::string line;
	//while we are reading each line
	while (std::getline(_databaseFile, line))
	{
		//create a string stream from the line
		std::stringstream ss(line);

		//assign the unique id 
		std::string uID;
		if (!std::getline(ss, uID, '/'))
		{
			//skip to the next line as we dont have a valid UID
			strtk001Utils::logError("cannot create patient as the uid is invalid is non existant");
			continue;
		}
		//assign DOB
		std::string dob;
		if (!std::getline(ss, dob, '/'))
		{
			//skip to the next line as we dont have a valid dob
			strtk001Utils::logError("cannot create patient as the dob is invalid is non existant");
			continue;
		}
		//generate age from dob
		std::istringstream dobSS(dob);
		std::tm t{};
		dobSS >> std::get_time(&t, "%d-%m-%Y");
		//assign the names
		std::string names;
		if (!std::getline(ss, names, '/'))
		{
			//skip to the next line as we dont have valid names
			strtk001Utils::logError("cannot create patient as the names are invalid or are non existant");
			continue;
		}
		//split the names string into tokens
		std::vector<std::string> nameTokens = splitString(names,',');
		//check the token count
		if (nameTokens.size() < 2)
		{
			//not enough names so skip to next line
			strtk001Utils::logError("cannot create patient as the nameTokens is < 2");
			continue;
		}
		//assign first and last names
		std::string lastName = nameTokens[0];
		std::string firstName = nameTokens[1];

		//create a new patient with the data so far
		Patient* patient = new Patient(firstName, lastName, t);

		//now we grab all the diseases the patient has
		std::string diseases;
		if (!std::getline(ss, diseases, '/'))
		{
			//skip to the next line as we dont have valid diseases
			strtk001Utils::logError("cannot create patient as the diseases is invalid is non existant");
			continue;
		}
		//similar to the names we now split the diseases
		std::vector<std::string> diseaseTokens = splitString(diseases,',');
		//inject the patient with all their diseases
		for (std::string disease : diseaseTokens)
		{
			patient->addDiagnosis(disease);
		}
		//lastly we'll grab the vital records
		std::string vitalString;
		//if successful in gettin the vitals
		if (std::getline(ss, vitalString, '/'))
		{
			//first split them via ;
			std::vector<std::string> vitalsClump = splitString(vitalString, ';');
			//then do another loop to split the clump
			for (std::string vitalsTokens : vitalsClump)
			{
				std::vector<std::string> vitalsToken = splitString(vitalsTokens, ',');
				//we're going to assume the data is correct for now
				//create new vitals
				Vitals* vitals = new Vitals(
					std::stoi(vitalsToken[0]),
					std::stoi(vitalsToken[1]),
					std::stoi(vitalsToken[2]),
					std::stoi(vitalsToken[3])
				);
				//add vitals to patient
				patient->addVitals(vitals);
			}
		}
		//add the patient to the patient vector
		patientIn.push_back(patient);
		strtk001Utils::logError("created: " + patientIn.back()->humanReadableID());
	}
}

std::vector<std::string> PatientCSVLoader::splitString(const std::string& str,char delimiter)
{
	std::stringstream ss(str);
	std::vector<std::string> tokens;
	std::string token;
	while (std::getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

bool PatientCSVLoader::openFile()
{
	_databaseFile.open(_filePath);
	if (!_databaseFile.is_open())
	{
		strtk001Utils::logError("cannot open or find file: " + _filePath);
		return false;
	}
	else
	{
		strtk001Utils::logError("found file: " + _filePath);
		return true;
	}
	
}

bool PatientCSVLoader::closeFile()
{
	if (!_databaseFile.is_open())
	{
		strtk001Utils::logError("cant close file: " + _filePath + " as it is not open");
		return false;
	}

	_databaseFile.close();

	if (_databaseFile.fail())
	{
		strtk001Utils::logError("failed to close file: " + _filePath);
		return false;
	}
	else
	{
		strtk001Utils::logError("sucessfully closed file: " + _filePath);
		return true;
	}
}