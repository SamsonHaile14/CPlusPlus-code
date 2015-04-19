#include "Deck.cpp"
#include <ncurses.h>
#include <iostream>

using namespace std;


int main()
	{
	 cout << (-6)%4 << endl;
	 initscr();
	 raw();

	 	Deck test, dest;

		test.buildFullDeck();
		test.shuffleDeck();


		test.relocateTop( dest );
		//test.relocateTop( dest );



		dest.displayDeck( false, 15, 10, 0, 0 );

		getch();


	 endwin();

	 return 0;


	}
