#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameObject.h"
#include <String.h>
#include <stdio.h>


using std::string;
using std::unique_ptr;

string commandBuffer;

State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r1 = new Room(&r1name, &r1desc);
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r5 = new Room(&r5name, &r5desc);
    auto * obj1 = new GameObject(&obj1name, &obj1desc, &obj1keyw);
    Room::addObj(obj1);
    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    r1->addObj(obj1);
    r1->setNorth(r2);
    r1->setSouth(r3);
    r1->setEast(r4);
    r1->setWest(r5);


}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}


/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */
        if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a north exit */
            Room *northRoom = currentState->getCurrentRoom()->getNorth();
            if (northRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(northRoom); /* Update state to that room - this will also describe it */
            }
        }
        if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a south exit */
            Room *southRoom = currentState->getCurrentRoom()->getSouth();
            if (southRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(southRoom); /* Update state to that room - this will also describe it */
            }
        }
        if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a east exit */
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            if (eastRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(eastRoom); /* Update state to that room - this will also describe it */
            }
        }
        if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a west exit */
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            if (westRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(westRoom); /* Update state to that room - this will also describe it */
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"back") == 0) || (commandBuffer.compare(0,endOfVerb,"b") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a previous room */
            Room *prevRoom = currentState->getPrevRoom();
            if (prevRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goBack(); /* Update state to that room - this will also describe it */
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"get") == 0)) {
            for(Room::obj_it = Room::room_objs.begin(); Room::obj_it != Room::room_objs.end(); Room::obj_it++) {
                string obj_name_tmp = reinterpret_cast<const char *>((*Room::obj_it)->getName());
                if (commandBuffer.compare(1, endOfVerb, obj_name_tmp) == 0) {
                    State::addObj((*Room::obj_it));
                    Room::remObj(((*Room::obj_it)));
                }
            }
        }

        if ((commandBuffer.compare(0, endOfVerb, "drop") == 0)) {
            for(Room::obj_it = State::inventory.begin(); Room::obj_it != State::inventory.end(); Room::obj_it++) {
                string obj_name_tmp = reinterpret_cast<const char *>((*Room::obj_it)->getName());
                if (commandBuffer.compare(1, endOfVerb, obj_name_tmp) == 0) {
                    State::remObj(*Room::obj_it);
                }
            }
        }

        if ((commandBuffer.compare(0, endOfVerb, "inventory") == 0)) {
            for(Room::obj_it = State::inventory.begin(); Room::obj_it != State::inventory.end(); Room::obj_it++) {
                wrapOut((*Room::obj_it)->getName());
                wrapEndPara();
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"examine") == 0)) {
            for(Room::obj_it = State::inventory.begin(); Room::obj_it != State::inventory.end(); Room::obj_it++) {
                string obj_name_tmp = reinterpret_cast<const char *>((*Room::obj_it)->getKeyword());
                if((commandBuffer.compare(1, endOfVerb, obj_name_tmp) == 0)) {
                    wrapOut((*Room::obj_it)->getDesc());
                    wrapEndPara();
                }
            }
        }

        /* Quit command */
        if ((commandBuffer.compare(0,endOfVerb,"quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}
