#ifndef CASCADE_H
#define CASCADE_H

#include "Includes.h"

class Cascade
{
private:
		GenArray<Puzzle>*	StateList;					// state list
		GenArray<Puzzle>*	WinStates;					// winning state list
		Puzzle winningState;							// winning state 

	public:
		Cascade( Puzzle* right );						// starting index is 0 in StateList

		int		addState	( Puzzle* right );			// add puzzle to array
		void	totalStates	( void );					// total number of state spaces
		bool	checkStates ( Puzzle* right );			// check array for current state; true if state is present
		Puzzle*	findWinner	( void );					// find and return the goal state

		bool processStateList	( void );				// generate state spaces	
		void drawStateList		( void );				// draw state list
		void walkthrough		( void );				// iterate through goal list set
};
#endif