#ifndef UTILITY_H
#define UTILITY_H

#include "PatientAlertLevels.h"
#include <iostream>
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
        std::cout << msg << std::endl;
    }
}


#endif