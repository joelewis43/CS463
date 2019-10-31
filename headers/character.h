#include "object.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Characther : public Object
{
    /**
     * Returns the ASCII character for the Character Object
     * 
     * @returns - The ASCII character for the Character Object
     **/
    const char toChar()
    {
        return '*';
    }

    /**
     * Returns the ID for the Character Object
     * 
     * @returns - The ID for the Character Object
     **/
    const char toID()
    {
        return '1';
    }
};

#endif // !CHARACTER_H
