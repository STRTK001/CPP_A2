#ifndef UTILITY_H
#define UTILITY_H

#include "PatientAlertLevels.h"
#include <iostream>
#include <vector>
#include <sstream>

//namespace for my utility junk.
namespace strtk001Utils
{
	inline std::string enumToString(AlertLevel en)
	{
        switch (en)
        {
        case AlertLevel::Red:
            return "Red";
        case AlertLevel::Orange:
            return "Orange";
        case AlertLevel::Yellow:
            return "Yellow";
        case AlertLevel::Green:
            return "Green";
        }
	}

    inline void logError(std::string msg)
    {
        std::cout <<"LOG: " << msg << std::endl;
    }

    inline std::vector<std::string> splitString(const std::string& str, char delimiter)
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

}


#endif