#include "Cascade.h"

Cascade::Cascade( Puzzle* right )
{
	StateList = new GenArray<Puzzle>( 10000, 10000 );
	WinStates = new GenArray<Puzzle>();
		
	StateList->Add( right );

}

int Cascade::addState( Puzzle* right )
{
	return StateList->Add( right );
}

void Cascade::totalStates( void )
{
	cout<<"\n\nTotal number of states are/is: "<<StateList->Top();
}

bool Cascade::checkStates( Puzzle* right )
{
	for( int i = 0; i < StateList->Top() ; i++ )
	{
		if( (*(*StateList)[i]).compare( *right ) == true )
			return true;
	}
	return false;
}

Puzzle* Cascade::findWinner( void )
{	
	cout<<"\nFinding winner... ";

	for( int i = 0 ; i < StateList->Top() ; i++ )
	{	
		if( (*(*StateList)[i]).checkWin() )
		{	
			return (*StateList)[i];
		}
	}
	cout<<"\n Not enough states in Cascade::findWinner";
	cout<<"\n Either increase the total number of states or lower the number of random moves ";
	return NULL;
}

bool Cascade::processStateList( void )
{
	cout<<"\nProcessing state list... ";
	Puzzle* temp;
	
	for( int i = 0 ; !(*(*StateList)[i]).checkWin() ; i++ )				// run until goal state is found
	{	
		if( !(*(*StateList)[i]).updated )								// has this grid been updated?
		{	
	// move up   ******************************************************************************************************************************
			if( (*(*StateList)[i]).peekMove( UP ) )						// can move up?
			{	
				temp = new Puzzle( (*(*StateList)[i]).getGrid() );		// create new object with current object parameters
				temp->me = temp;										// object stores location of itself to link states
				temp->from = (*(*StateList)[i]).me;						// link current object to new object
				temp->updateGrid( false );
				temp->move( UP );										// commit move to new object
				temp->updateGrid( false );
				temp->cost = (*(*StateList)[i]).cost + 1;				// increase cost

				if( !checkStates( temp ) )								// is state present in array?
					StateList->Add( temp );								// if not - add state
			}

	// move left ******************************************************************************************************************************
			if( (*(*StateList)[i]).peekMove( LEFT ) )					// can move left?
			{	
				temp = new Puzzle( (*(*StateList)[i]).getGrid() );		// create new object with current object parameters
				temp->me = temp;										// object stores location of itself to link states
				temp->from = (*(*StateList)[i]).me;						// link current object to new object
				temp->updateGrid( false );
				temp->move( LEFT );										// commit move to new object
				temp->updateGrid( false );
				temp->cost = (*(*StateList)[i]).cost + 1;				// increase cost

				if( !checkStates( temp ) )								// is state present in array?
					StateList->Add( temp );								// if not - add state
			}

	// move down ******************************************************************************************************************************
			if( (*(*StateList)[i]).peekMove( DOWN ) )					// can move down?
			{	
				temp = new Puzzle( (*(*StateList)[i]).getGrid() );		// create new object with current object parameters
				temp->me = temp;										// object stores location of itself to link states
				temp->from = (*(*StateList)[i]).me;						// link current object to new object
				temp->updateGrid( false );
				temp->move( DOWN );										// commit move to new object
				temp->updateGrid( false );
				temp->cost = (*(*StateList)[i]).cost + 1;				// increase cost

				if( !checkStates( temp ) )								// is state present in array?
					StateList->Add( temp );								// if not - add state
			}

	// move right ******************************************************************************************************************************
			if( (*(*StateList)[i]).peekMove( RIGHT ) )					// can move right?
			{	
				temp = new Puzzle( (*(*StateList)[i]).getGrid() );		// create new object with current object parameters
				temp->me = temp;										// object stores location of itself to link states
				temp->from = (*(*StateList)[i]).me;						// link current object to new object
				temp->updateGrid( false );
				temp->move( RIGHT );									// commit move to new object
				temp->updateGrid( false );
				temp->cost = (*(*StateList)[i]).cost + 1;				// increase cost

				if( !checkStates( temp ) )								// is state present in array?
					StateList->Add( temp );								// if not - add state
			}

			(*(*StateList)[i]).updated = true;
		}
	}
	return true;
}

void Cascade::drawStateList( void )
{
	for( int i = 0 ; i < StateList->Top() ; i++ )
	{
		cout<<"\nIndex: "<<i;
		cout<<"\nCost: "<<(*(*StateList)[i]).cost;
		(*(*StateList)[i]).drawGrid();
	}
}

void Cascade::walkthrough( void )
{
	Puzzle* temp1 = findWinner();		// find winning state
	Puzzle* temp2 = temp1;				// remember winner location
	char input = '_';					// hold user input
	
	while( temp1->from != NULL )		// trace back to original state
	{
		WinStates->Add( temp1 );
		temp1 = temp1->from;
	}

	cout<<"\n\n\n***********************************************************************";
	cout<<"\nTotal number of states generated: "<<StateList->Top();
	cout<<"\nTotal moves to solve grid = "<<WinStates->Top() - 1;
	cout<<"\n***********************************************************************";

	for( int i = WinStates->Top() - 1 ; i >= 0 && input != 'q' ; i-- )
	{
		cout<<"\nCurrent state: ";
		(*(*WinStates)[i]).drawGrid();
		cout<<"\n\nYou are tracing through the state list ";
		cout<<"\nPress \"e\" to continue, or \"q\" to quit: ";
			cin>>input;
	}
};