#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Patient.h"
#include "Vitals.h"
#include "Utility.h"

PatientFileLoader::PatientFileLoader(const std::string& file) :
    _file(file)
{
}

std::vector<Patient*> PatientFileLoader::loadPatientFile()
{
    std::vector<Patient*> patients;

    std::ifstream inFile(_file);
    if (inFile.is_open()) {
		//store an empty string to represent a line
		std::string line;
		//while we are reading each line
		while (std::getline(inFile, line))
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
			std::vector<std::string> nameTokens = strtk001Utils::splitString(names, ',');
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
			std::vector<std::string> diseaseTokens = strtk001Utils::splitString(diseases, ',');
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
				std::vector<std::string> vitalsClump = strtk001Utils::splitString(vitalString, ';');
				//then do another loop to split the clump
				for (std::string vitalsTokens : vitalsClump)
				{
					std::vector<std::string> vitalsToken = strtk001Utils::splitString(vitalsTokens, ',');
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
			patients.push_back(patient);
			//strtk001Utils::logError("created: " + patients.back()->humanReadableID());
		}
    }
    return patients;
}
