#include "GeneralTools.h"

unsigned int linesInString(const std::string& t_rString)
{
    unsigned int lines = 1;
    for (unsigned int i = 0; i < t_rString.size(); ++i)
    {
        if (t_rString[i] == '\n')
        {
            ++lines;
        }
    }
    return lines;
}


unsigned int lastLineLength(const std::string& t_rString)
{
    unsigned int len = 0;
    for(unsigned int i = 0; i < t_rString.size(); ++i)
    {
        if (t_rString[i] == '\n')
        {
            len = 0;
        } else {
            ++len;
        }
    }
    return len;
}