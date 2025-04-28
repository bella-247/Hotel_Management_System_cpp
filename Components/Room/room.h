#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include "../../Structures/structures.h"
#include "../../Database/database.h"
#include "roomtypes.h"

using namespace std;

// helper functions
bool getRoomById(int room_id, Room &room);
bool getRoomByRoomNumber(int room_number, Room &room);
bool validateRoomNumber(int &room_number);

// room menu functions
Room addRoom();
void removeRoom();

// room functions
void bookRoom();
void showAvailableRooms();
void showRoomsByTypes();
void showRoomDetails(int room_number);
void leaveRoom();

void showRooms();
void getRooms();
int RoomCallback(void* data, int columns, char** values, char** column_names);

#endif
