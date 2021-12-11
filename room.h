#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include "GameObject.h"

using std::string;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;
    /**
     * Pointer to room that is n/s/e/w of this one.
     */
    Room* north;
    Room* south;
    Room* east;
    Room* west;

public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;

    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::list<Room*> rooms;

    /**
     * list of game objects in room
     */
    static std::list<GameObject*> room_objs;
    static std::list<GameObject*>::iterator obj_it;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);

    static void addObj(GameObject* obj) {};
    static void remObj(GameObject* obj) {};


    Room* getNorth() const;
    Room* getSouth() const;
    Room* getEast() const;
    Room* getWest() const;
    void setNorth(Room* _north);
    void setSouth(Room* _north);
    void setEast(Room* _north);
    void setWest(Room* _north);

};

#endif //TEXTADV_ROOM_H
