#ifndef PUZZLE_H
#define PUZZLE_H

#include "Includes.h"

#define UP		'W'
#define LEFT	'A'
#define DOWN	'S'
#define RIGHT	'D'


class Puzzle
{	
	private:
		bool	visited[4][4];												// visited nodes
		int		Grid[4][4];													// grid for numbers
		int		x, y;														// position of command block

	public:
		Puzzle();															// default solveable array
		Puzzle( int preset[16] );											// preset Puzzle 2-D array
		Puzzle( int preset[16], Puzzle* rfrom, Puzzle* rto, int rcost );	// for cascade
		
		Puzzle operator=( Puzzle &right );		// copy

		// grid functions
		int	 randomizeGrid	( void );			// randomize grid and return total number of sucessful moves
		void drawGrid		( void );			// update grid and draw
		void drawVisited	( void );			// draw update grid
		void updateGrid		( bool isVisit);	// update grid; if visit is true: update visited indexes as well
		bool checkWin		( void );			// see if grid solution wins game
		bool compare		( Puzzle &puz );	// compare a puzzle's grid to another Puzzle Grid; returns true if same

		// accessors/mutators
		int	 getX			( void );			// return x position of command block
		int  getY			( void );			// return y position of command block
		int  getGridIndex	( int x, int y );	// return Grid[x][y] index
		int* getGrid		( void );			// return pointer to Grid
		bool getVisited		( int x, int y );	// return visited[x][y]
		int* exportArray	( void );			// return a pointer to a 1-D array (dynamic mem alloc)

		// movement - command block
		bool move			( char sel );		// movement of command block is handled through here. Returns true if move was sucessful
		bool peekMove		( char sel );		// test move; returns true if move is possible
		bool swapElements	( int x, int y );	// takes input from move(), checks bounds, and returns whether move was successful

		// for console testing
		void consoleTest	( void );			// call this to start the game
		void inputPrompt	( bool visit );		// prompt user for moves (called by console test); true to draw visited grid


		///////////////////////////////////////////////////////////////////////////////////////
		//  (~ ;_; )~   //
		//////////////////////////////////////////////////////////////////////////////////////
		// *************************************************************************** cascade
		GenArray<Puzzle> StateList;
		Puzzle* from;							// from grid
		Puzzle* me;								// itself
		int		cost;							// running cost
		bool	updated;						// has this been processed before?

// /cascade *****************************************************************************
		~Puzzle();
};
#endif