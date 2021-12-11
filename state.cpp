#include "State.h"
#include "GameObject.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

std::list<GameObject*> State::inventory;

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->previousRoom = currentRoom;
    this->currentRoom = target;
    this->announceLoc();
}

void State::goBack() {
    goTo(previousRoom);
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

Room* State::getPrevRoom() const {
    return this->previousRoom;
}

void State::addObj(GameObject *obj) {
    State::inventory.push_back(obj);
}

void State::remObj(GameObject *obj) {
    State::inventory.remove(obj);
}
