#include "object.h"

#ifndef COMET_H
#define COMET_H

class Comet : public Object
{
    /**
     * Returns the ASCII character for the Comet Object
     * 
     * @returns - The ASCII character for the Comet Object
     **/
    const char toChar()
    {
        return '#';
    }

    /**
     * Returns the ID for the Comet Object
     * 
     * @returns - The ID for the Comet Object
     **/
    const char toID()
    {
        return '2';
    }
};

#endif // !COMET_H
