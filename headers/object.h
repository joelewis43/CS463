#ifndef OBJECT_H
#define OBJECT_H

class Object
{
protected:
    // X-Coordinate for the Object
    int xpos;
    // Y-Coordinate for the Object
    int ypos;

public:
    /**
     * Getter for the x-coordinate
     * 
     * @returns - The x-coordinate position
     **/
    int xPos() { return xpos; };

    /**
     * Getter for the y-coordinate
     * 
     * @returns - The y-coordinate position
     **/
    int yPos() { return ypos; };

    /**
     * Setter for the x-coordinate
     * 
     * @params x - Value for the x-coordinate
     **/
    void xPos(int x) { xpos = x; };

    /**
     * Setter for the y-coordinate
     * 
     * @params y - Value for the y-coordinate
     **/
    void yPos(int y) { ypos = y; };

    /**
     * Returns the ID for the Object
     * 
     * @returns - The ID for the Object
     **/
    virtual const char toID() = 0;

    /**
     * Returns the ASCII character for the Object
     * 
     * @returns - The ASCII character for the Object
     **/
    virtual const char toChar() = 0;

    virtual ~Object() {};
};

#endif // !OBJECT_H
