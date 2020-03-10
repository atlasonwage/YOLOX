#pragma once
#include <string>

//Defines the underlying storage method for type id types.
typedef unsigned int TID;

namespace TypeService
{
    //primitives
    constexpr TID _void = 0;
    constexpr TID error = 1;
    constexpr TID number = 2;
    constexpr TID string = 3;
    constexpr TID boolean = 4;

    struct TypeInfo
    {
        std::string name;
        const TID id;
        const std::string * aMembers;   //nullptr   for primitives
        const TID * aTypes;             //nullptr   for primitives
        const TID numTypes;             //0         for primitives
    };

    const TypeInfo getInfo(const TID t_type);
    const TypeInfo getInfo(const std::string& t_rStr);

    /**
     * Adds a new type to the service, if it does not already exist,
     * @param t_rStr        The string name of the type.
     * @param t_aTypes      A dynamically-allocated array containing all types.
     * @param t_aMembers    The names of all of the members.
     * @param t_numTypes    The number of types in the array.
     * @return The TID of the type.
     */
    const TypeInfo addType(const std::string& t_rStr, const TID * const t_aTypes,
        const std::string * const t_aMembers, const unsigned int t_numTypes);


    //Does set-up.  Run once before this service is used.
    void initialize();

    //Cleans up all dynamically-allocated arrays.
    void cleanUp();
}
