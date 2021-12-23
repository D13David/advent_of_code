#include <stdlib.h>
#include <stdio.h>

#define PART 2

/*
	Note:
		instead of solving it on paper one can handle this as a search problem. i.e. run dijkstra on the graph of all potential
		moves. for every board state (position of entities in hallway or rooms) the set of potential next moves is determined
		with the cost being the energy consumtion of the entity moving from base to next move. the moves are potential moves
		of entities from room to hallway (4 entities * 7 positions in hallway) and the potential moves of entities from hallway
		to rooms (7 positions in hallway * 4 rooms). if a room is empty, or a hallway position is not occupied or the path from
		start to target is blocked by another entity the move is skipped as not valid.

		the movement rules of entities are:
		* Amphipods will never stop on the space immediately outside any room. They can move into that space so long as they immediately 
			continue moving. (Specifically, this refers to the four open spaces in the hallway that are directly above an amphipod 
			starting position.)
		* Amphipods will never move from the hallway into a room unless that room is their destination room and that room contains no 
			amphipods which do not also have that room as their own destination. If an amphipod's starting room is not its destination 
			room, it can stay in that room until it leaves the room. (For example, an Amber amphipod will not move from the hallway into 
			the right three rooms, and will only move into the leftmost room if that room is empty or if it only contains other Amber 
			amphipods.)
		* Once an amphipod stops moving in the hallway, it will stay in that spot until it can move into a room. (That is, once any amphipod 
			starts moving, any other amphipods currently in the hallway are locked in place and will not move again until they can move 
			fully into a room.)

	Part 1
	#############
	#...........#
	###B#A#B#C###
	  #D#A#D#C#
	  #########

	#############
	#AA.........#
	###B#.#B#C###  A * 5 + A * 5 = 10
	  #D#.#D#C#
	  #########

	#############
	#AA.........#
	###.#B#.#C###  B * 5 + B * 4 = 90
	  #D#B#D#C#
	  #########

	#############
	#AA...C...C.#
	###.#B#.#.###  C * 2 + C * 5 = 700
	  #D#B#D#.#
	  #########

	#############
	#AA...C...C.#
	###.#B#.#.###  D * 6 = 6000
	  #D#B#.#D#
	  #########

	#############
	#AA.........#
	###.#B#C#.###  C * 3 + C * 4 = 700
	  #D#B#C#D#
	  #########

	#############
	#AA.........#
	###.#B#C#D###  D * 9 = 9000
	  #.#B#C#D#
	  #########

	#############
	#AA.........#
	###.#B#C#D###  A * 3 + A * 3 = 6
	  #.#B#C#D#
	  #########

	Part 2
	#############
	#...........#
	###B#A#B#C###
	  #D#C#B#A#
	  #D#B#A#C#
	  #D#A#D#C#
	  #########

	#############
	#..........A#
	###B#.#B#C###	A * 7 = 7
	  #D#C#B#A#
	  #D#B#A#C#
	  #D#A#D#C#
	  #########

	#############
	#.......C..A#
	###B#.#B#C###  C * 5 = 500
	  #D#.#B#A#
	  #D#B#A#C#
	  #D#A#D#C#
	  #########

	#############
	#.....B.C..A#
	###B#.#B#C###  B * 4 = 40
	  #D#.#B#A#
	  #D#.#A#C#
	  #D#A#D#C#
	  #########

	#############
	#A....B.C..A#
	###B#.#B#C###  A * 8 = 8
	  #D#.#B#A#
	  #D#.#A#C#
	  #D#.#D#C#
	  #########

	#############
	#A......C..A#
	###.#B#.#C###  B * 5 + B * 6 + B * 5 + B * 5 = 210
	  #D#B#.#A#
	  #D#B#A#C#
	  #D#B#D#C#
	  #########

	#############
	#AA.....C..A#
	###.#B#.#C###  A * 8 = 8
	  #D#B#.#A#
	  #D#B#.#C#
	  #D#B#D#C#
	  #########

	#############
	#AA...D.C..A#
	###.#B#.#C###  D * 5 = 5000
	  #D#B#.#A#
	  #D#B#.#C#
	  #D#B#.#C#
	  #########

	#############
	#AA...D....A#
	###.#B#.#.###  C * 5 + C * 6 = 1100
	  #D#B#.#A#
	  #D#B#C#C#
	  #D#B#C#C#
	  #########

	#############
	#AA...D...AA#
	###.#B#.#.###  A * 3 = 3
	  #D#B#.#.#
	  #D#B#C#C#
	  #D#B#C#C#
	  #########

	#############
	#AA...D...AA#
	###.#B#C#.###  C * 7 + C * 7 = 1400
	  #D#B#C#.#
	  #D#B#C#.#
	  #D#B#C#.#
	  #########

	#############
	#AA.......AA#
	###.#B#C#D###  D * 7 + D * 11 + D * 11 + D * 11 = 40000
	  #.#B#C#D#
	  #.#B#C#D#
	  #.#B#C#D#
	  #########

	#############
	#AA.......AA#
	###.#B#C#D###  A * 5 + A * 5 + A * 9 + A * 9 = 28
	  #.#B#C#D#
	  #.#B#C#D#
	  #.#B#C#D#
	  #########
*/

enum Type
{
	A, B, C, D
};

int Cost(char type)
{
	switch (type)
	{
	case A: return 1;
	case B: return 10;
	case C: return 100;
	case D: return 1000;
	}
	return 0;
}

int main()
{
#if PART == 1
	int path[] = { A, 5, A, 5, B, 5, B, 4, C, 2, C, 5, D, 6, C, 3, C, 4, D, 9, A, 3, A, 3 };
#else
	int path[] = { A, 7, C, 5, B, 4, A, 8, B, 5, B, 6, B, 5, B, 5, A, 8, D, 5, C, 5, C, 6, A, 3, C, 7, C, 7, D, 7, D, 11, D, 11, D, 11, A, 5, A, 5, A, 9, A, 9 };
#endif

	int sum = 0;
	for (int i = 0; i < _countof(path); i += 2)
	{
		sum += Cost(path[i]) * path[i + 1];
	}

	printf("%d\n", sum);
}