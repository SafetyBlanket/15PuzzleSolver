#include "Includes.h"

int main()
{	

	Puzzle test1;
	test1.me = &test1;										// location of itself (for cascade)
	cout<<"\nRandom moves made: "<<test1.randomizeGrid();	// total number of random moves made within bounds
	Cascade testCascade( &test1 );							// object to cascade state spaces - uses parameter as starting space

	testCascade.processStateList();							// cascade and generate state spaces
	testCascade.walkthrough();								// cascade user prompt

//	testCascade.drawStateList();		// draw all the states created

	system("pause");
	return 0;
}