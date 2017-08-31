#include "Includes.h"

Puzzle::Puzzle()
{	
	int numArray[16];	
	int x = 0;
	int y = 0;
	updated = false;

	from = NULL;
	cost = 0;

	for ( int i = 0, num = 1; i < 16 ; i++ )
	{
		numArray[i] = num;
		num++;
	}

	for (int i = 0, j = 0, p = 0 ; i < 4 ; i++)
	{	
		while( j < 4 )	
		{	
			visited[i][j] = false;
			Grid[i][j] = numArray[p];
			p++; 
			j++;
		}
		j = 0;
	}

}

Puzzle::Puzzle( int preset[16] )
{	
	int x = 0;
	int y = 0;
	from = NULL;
	cost = 0;
	updated = false;

	for (int i = 0, j = 0, p = 0 ; i < 4 ; i++)
	{	
		while( j < 4 )	
		{	
			visited[j][i] = false;
			Grid[i][j] = *(preset + p);
			p++; 
			j++;
		}
		j = 0;
	}	
	// setup Grid with x and y values
	updateGrid( false );
}

Puzzle::Puzzle( int preset[16], Puzzle* rfrom, Puzzle* rto, int rcost )
{
	from = rfrom;
	cost = rcost;
	updated = false;

	for (int i = 0, j = 0, p = 0 ; i < 4 ; i++)
	{	
		while( j < 4 )	
		{	
			visited[j][i] = false;
			Grid[i][j] = *(preset + p);
			p++; 
			j++;
		}
		j = 0;
	}	

	updateGrid( false );
	// rest of definitions will be handled through cascade
}

Puzzle Puzzle::operator=( Puzzle &right )
{
	for(int i = 0, j = 0; i < 4 ; i++)
	{
		for( ; j < 4 ; j++ )
		{
			visited[i][j] = right.getVisited( i, j );
			Grid[i][j] = right.getGridIndex( i, j );
		}
		j = 0;
	}
		x = right.getX();
		y = right.getY();
	return *this;
}

Puzzle::~Puzzle()
{
}

int* Puzzle::exportArray ( void )
{
	int* temp;
	temp = new  int [16];
	
	for( int i = 0, j = 0, p = 0; p < 4 ; p++ )
	{
		for( ; j < 4 ; j++ )
		{
			temp[i] = Grid[j][p];
			i++;
		}
		j = 0;
	}
	return temp;
}

int Puzzle::randomizeGrid( void )
{
	int numMoves;			// random number of moves
	int moveDir;			// random move

	unsigned timeSeed = int ( time(0) );
	srand(timeSeed);

//	numMoves = rand();		// random number of random moves
	numMoves = 20;

	/////////////////////////////////////////////////////////////////////////////
	// dubgging for cascade
	/////////////////////////////////////////////////////////////////////////////
	int totalranmoves = 0;


	cout<<"\nRandomizing Grid...";
	for( int i = 0; i <= numMoves ; i++ )
	{	
		moveDir = 1 + rand() % 4;

		switch( moveDir )
		{
				case 1:
					move( 'W' );
											if( peekMove( UP ) ){
												totalranmoves+=1; cout<<"\nmoved up";}
					updateGrid( false );
					break;

				case 2:
					move( 'A' );
											if( peekMove( LEFT ) ){
												totalranmoves+=1; cout<<"\nmoved left"; }
					updateGrid( false );
					break;

				case 3:
					move( 'S' );
											if( peekMove( DOWN ) ){
												totalranmoves+=1; cout<<"\nmoved down"; }
					updateGrid( false );
					break;

				case 4:
					move( 'D' );
											if( peekMove( RIGHT ) ){
												totalranmoves+=1; cout<<"\nmoved right"; }
					updateGrid( false );
					break;

				default:
					cout<<"\nrandomizeGrid() failed! ";
					break;
		}
	}
	return totalranmoves;
}

bool Puzzle::checkWin( void )
{
	updateGrid( false );
	for( int i = 0, j = 0, counter = 1 ; i < 4 ; i++ )
	{
		for( ; j < 4 ; j++ )
		{	
			if( Grid[i][j] != counter )
			return false;
			counter++;
		}
		j = 0;
	}
	return true;
}

void Puzzle::drawGrid (void)
{
	cout<<"\n----------------------"<<endl;
	for(int i = 0, j = 0 ; i < 4 ; i++ )
	{	
		cout<<"\n | ";

		for( ; j < 4 ; j++ )
		{	
			if ( Grid[i][j] == 16)
			{	cout<<setw( 2 )<<"  "<<" | ";

				x = i;	// cursor x position
				y = j;	// cursor y position

				visited[i][j] = true;	// set node to visited
			}
			else
				cout<<setw( 2 )<<Grid[i][j]<<" | ";
		}
		j = 0;
	}
	cout<<"\n----------------------"<<endl;
}

void Puzzle::drawVisited( void )
{
	cout<<"\n----------------------"<<endl;
	for(int i = 0, j = 0 ; i < 4 ; i++ )
	{	
		cout<<"\n | ";

		for( ; j < 4 ; j++ )
		{	
				cout<<setw( 2 )<<visited[i][j]<<" | ";
		}
		j = 0;
	}
	cout<<"\n----------------------"<<endl;
}

void Puzzle::updateGrid ( bool isVisit )
{
	for(int i = 0, j = 0 ; i < 4 ; i++ )
	{	

		for( ; j < 4 ; j++ )
		{	

			if ( Grid[i][j] == 16)
			{	

				x = i;	// cursor x position
				y = j;	// cursor y position

				if( isVisit )
				visited[i][j] = true;	// set node to visited
			}
		}
		j = 0;
	}
}

void Puzzle::inputPrompt( bool visit )
{
	cout<<"\n\n\n\n\nYou are controlling the empty cube:";
	cout<<"\nUse \"W\" (up) \"A\" (left) \"S\" (down) \"D\" (right) \"Q\" (quit)";
	cout<<"\n\nplease enter a WASD selection and press \"Enter\": ";

	char move = '_', selection = '_';

	// lazy...
	while( true )
	{	
		drawGrid();
		
		if( visit == true )
		drawVisited();

		cout<<"\nPlease enter a selection: ";
		cin>>selection;

		if( toupper(selection) == 'Q' )
			break;

		if( !Puzzle::move(selection) )
			cout<<"\nError! Please make a valid selection. ";

		else
		updateGrid(true);
	}
}

void Puzzle::consoleTest( void )
{
	randomizeGrid();
	inputPrompt( true );

}

bool Puzzle::swapElements (	int horizontal, int vertical )
{
	// variables to handle rotation of data
	int temp = 0, temp1 = 0;

	// check bounds before moving
	if ( (horizontal + x) > 3 ||
		 (horizontal + x) < 0 ||
		 (vertical + y  ) > 3 ||
		 (vertical + y  ) < 0	)
	{
			return false;
	}
	// current location of square
	temp = *(*(Grid + x) + y);
	
	// destination of square
	temp1 = *(*(Grid + x + horizontal) + y + vertical);
	
	// assign destination (temp1) to old location
	*(*(Grid + x) + y) = temp1;

	// assign current location to destination
	*(*(Grid + x + horizontal) + y + vertical) = temp;

	return true;
}

bool Puzzle::move ( char sel )
{
	updateGrid( false );	// edit*******************************
		switch ( toupper(sel) )
		{
			case 'W':	
						if( !swapElements(-1, 0) )
							return false;
						else
							return true;
			case 'A':
						if( !swapElements(0, -1) )
							return false;
						else
							return true;
			case 'S':
						if( !swapElements(1, 0) )
							return false;
						else
							return true;
			case 'D':
						if( !swapElements(0, 1) )
							return false;
						else
							return true;
			default:
				return false;

		}
		return true;
}

bool Puzzle::peekMove( char sel )
{
	int horizontal = 0;
	int vertical = 0;

		switch ( toupper(sel) )
		{
			case 'W':	
						horizontal = -1; vertical = 0;
							break;
			case 'A':
						horizontal = 0; vertical = -1;
							break;
			case 'S':
						horizontal = 1; vertical = 0;
							break;
			case 'D':
						horizontal = 0; vertical = 1;
							break;
			default:
				return false;

		}

	// check bounds;
	if ( (horizontal + x) > 3 ||
		 (horizontal + x) < 0 ||
		 (vertical + y  ) > 3 ||
		 (vertical + y  ) < 0	)
	{	return false; }
		
	else
		return true;
}

int Puzzle::getGridIndex( int x, int y )
{
	int temp = Grid[x][y];
	return temp;
}

int* Puzzle::getGrid( void )
{
	return *Grid;
}

bool Puzzle::getVisited( int x, int y )
{
	return visited[x][y];
}

bool Puzzle::compare( Puzzle &puz )
{	
	for( int i = 0, j = 0; i < 4 ; i++ )
	{
		for( ; j < 4 ; j++ )
		{	
			if( Grid[i][j] != puz.getGridIndex( i, j ) )
				 return false;
		}
		j = 0;
	}
	return true;
}

int Puzzle::getX( void )
{ return x; }

int Puzzle::getY( void )
{ return y; }
