#pragma once
#include <string>

//Defines the underlying storage method for type id types.
typedef unsigned int TID;

namespace TypeService
{
    constexpr TID _void = 0;
    constexpr TID error = 1;
    constexpr TID number = 2;
    constexpr TID string = 3;
    constexpr TID boolean = 4;

    struct TypeInfo
    {
        std::string name;
        TID value;
    };

    const TypeInfo getInfo(const TID t_type);
    const TypeInfo getInfo(const std::string& t_rStr);

    /**
     * Adds a new type to the service, if it does not already exist,
     * @param t_rStr The string name of the type.
     * @return The TID of the type.
     */
    const TypeInfo addType(const std::string& t_rStr);

    //Does set-up.  Run once before this service is used.
    void initialize();
}
