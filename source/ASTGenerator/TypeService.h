#pragma once
#include <string>

//Defines the underlying storage method for type id types.
typedef unsigned int TID;

namespace TypeService
{
    constexpr TID error = 0;
    constexpr TID number = 1;
    constexpr TID string = 2;
    constexpr TID boolean = 3;

    std::string getNameFromTID(const TID t_type);
    TID getTIDFromName(const std::string& t_rStr);

    /**
     * Adds a new type to the service, if it does not already exist,
     * @param t_rStr The string name of the type.
     * @return The TID of the type.
     */
    TID addType(const std::string& t_rStr);

    //Does set-up.  Run once before this service is used.
    void initialize();
}
