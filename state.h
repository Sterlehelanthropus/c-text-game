#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H

#include "Room.h"
#include "GameObject.h"

class State {
    Room *currentRoom;
    Room *previousRoom;
public:
    explicit State(Room *startRoom);
    static std::list<GameObject*> inventory;
    void goTo(Room *target);
    void goBack();
    void announceLoc() const;
    static void addObj(GameObject *obj);
    static void remObj(Gameobject *obj);
    Room* getCurrentRoom() const;
    Room* getPrevRoom() const;
};

#endif //TEXTADV_STATE_H
