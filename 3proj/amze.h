/* Ian J */

#ifndef AMZE_H
#define AMZE_H value

struct vbentry {
	int iRat; /* rat identifier */
	int tEntry; /* time of entry into room */
	int tDep; /* time of departure from room */
};


int TryToEnterRoom(int iRat, int iRoom);
/* iRat - id of rat entering the room */
/* iRoom - id of room being entered */
void EnterRoom(int iRat, int iRoom);
/* iRat - id of rat entering the room */
/* iRoom - id of room being entered */
void LeaveRoom(int iRat, int iRoom, int tEnter);
/* iRat - id of rat leaving the room */
/* iRoom - id of room being left */
/* tEnter - time Rat entered room */

#endif
