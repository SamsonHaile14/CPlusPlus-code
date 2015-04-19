#include <ncurses.h>
#include <stack>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

struct Card{

string suit;
int rank;	//11 = jack, 12 = queen, 13 = king

};

class Deck{

public:
Deck();
~Deck();
void shuffleDeck();
void relocateTop( Deck& dest );
void displayDeck( bool faceDown, int cardWidth, int cardHeight, int tLXCorner,
		  int tLYCorner );
void removeOutline( int cardWidth, int cardHeight, int tLXCorner,
		    int tLYCorner );
void dumpDeck();
void buildFullDeck();

int size();
bool empty();
Card topInfo();

private:
stack<Card> set;
Card removeCard();

};

Deck::Deck()
	{
	 //start with empty deck
	}

Deck::~Deck()
	{
	 //nothing to do here
	}

void Deck::shuffleDeck()
	{

	 if( set.empty() || (set.size() == 1) )	//don't shuffle what you don't have
	    return;

	 Card temp;	//variables used for shuffle process
	 int num, numTheSequel, amount;

	 srand((unsigned) time(NULL) );	//make randomness

	 amount = set.size();
	 Card shufflePile[set.size()];	//container for shuffling

	 for( int a = 0; a < amount; a++ )//transfer cards to a vector
		 shufflePile[a] = removeCard();

	 for( int count = 0; count < 10000; count++ )	//swap 10000 times
	     {
	      num = rand() % amount;	//create random numbers
	      numTheSequel = rand() % amount;

	      temp = shufflePile[num];
	      shufflePile[num] = shufflePile[numTheSequel];
	      shufflePile[numTheSequel] = temp;
	     }

	 for( int a = 0; a < amount; a++ )//transfer cards back to stack
		set.push(shufflePile[a]); 

	}

void Deck::relocateTop( Deck& dest )
	{


	 if( !(empty()) )	//ensure there are cards to be moved
		{

		 dest.set.push( removeCard() );	//relocate card to dest deck

		}
	}

void Deck::displayDeck( bool faceDown, int cardWidth, int cardHeight, int tLXCorner,
		  int tLYCorner )
	{

	 if( ( cardWidth > 11 ) && ( cardHeight > 3 ) )  //cards must have sufficient width and height
		{

		 for( int x = 0; x<cardWidth; x++ )	//form top border
		     mvaddch( tLYCorner, tLXCorner + x, '-' );


		 if( (faceDown) || (set.empty()) )	//printing empty/back of card
			{

			 for( int a = 1; a<(cardHeight-1); a++ )//print card from top to bottom
				{
				 mvaddch( tLYCorner + a, tLXCorner, '|' );//left border

				 for( int b = 1; b<(cardWidth-1); b++ )//print from left to right
					{

					 if( set.empty() ) //print card outline
						mvaddch( tLYCorner + a, tLXCorner + b, ' ' );

					 else //print back of card
						mvaddch( tLYCorner + a, tLXCorner + b, 'x' );

					}					

				 mvaddch( tLYCorner + a, tLXCorner+(cardWidth-1), '|' ); //right border
						
				}

		 	 for( int x = 0; x<cardWidth; x++ )	//form bottom border
				mvaddch( tLYCorner+(cardHeight-1), tLXCorner + x, '-' );

			}

		 else	//otherwise, print contents of deck
			{
			 int amount, a;
			 Card display[set.size()];
			 amount = set.size();

			 for( a=amount-1; a>-1; a-- )
			    display[a] = removeCard();

			 for( a = 0; a<(amount); a++ )
				{

				 mvaddch( tLYCorner + 2*(amount-a)-1, tLXCorner, '|' );//left border

				 printw( "%s", display[amount-a-1].suit.c_str() );
				 addch( ' ' );
				 addch( char( '0' + display[amount-a-1].rank/10 ) );
				 addch( char( '0' + display[amount-a-1].rank%10 ) );

				 for( int x = 0; x<(cardWidth-5-display[amount-a-1].suit.size()); x++)
					addch( ' ' );

				 mvaddch( tLYCorner + 2*(amount-a)-1, tLXCorner + (cardWidth-1), '|' );//right border

				 if( a != (amount-1) )
					{
					 for( int x = 0; x<cardWidth; x++ )	//form bottom border
						mvaddch( tLYCorner+ 2*(a)+2, tLXCorner + x, '-' );
					}

				}

			 for( a = 0; a < (cardHeight-3); a++ )
				{
				 mvaddch( tLYCorner + 2*amount + a, tLXCorner, '|' );//left border

				 for( int b = 1; b<(cardWidth-1); b++ )//print from left to right
					mvaddch( tLYCorner + 2*amount + a, tLXCorner + b, ' ' );
			      
				 mvaddch( tLYCorner + 2*amount + a, tLXCorner + (cardWidth-1), '|' );//right border
				}

			 for( a = 0; a<amount; a++ )//recreate deck
				set.push(display[a]);

			 for( int x = 0; x<cardWidth; x++ )	//form bottom border
				 mvaddch( tLYCorner + 2*amount + cardHeight - 3, tLXCorner + x, '-' );//right border

			}		

		}
	}

void Deck::removeOutline( int cardWidth, int cardHeight, int tLXCorner,
		    int tLYCorner )
	{

	 for( int y = 0; y<cardHeight; y++ )
		{

		 for( int x = 0; x<cardWidth; x++ )
			mvaddch( tLYCorner + y, tLXCorner + x, ' ' );

		}

	}

void Deck::dumpDeck()
	{

	 while( !(set.empty()) )
		set.pop();

	}

void Deck::buildFullDeck()
	{

	 string names[4] = { "Spades", "Diamonds", "Clubs", "Hearts" };
	 Card copy;

	 for( int a = 0; a<4; a++ )	//loop through suits
		{

		 copy.suit = names[a];
	
		 for( int b = 1; b< 14; b++ )	//loop through ranks
			{
			  
			 copy.rank = b;		//add card to deck stack
			 set.push(copy);

			}
		}

	}

Card Deck::removeCard()
	{

	 if( !(set.empty()) )	//remove and return card if it exists
	   {
	    Card removed = set.top();
	    set.pop();
	    return removed;
	   }

	 else			//otherwiser, give user a blank card
	    {
	     Card empty;
	     empty.suit = "empty";
	     empty.rank = 0;

	    }
	}

bool Deck::empty()
	{

	 return set.empty();

	}

Card Deck::topInfo()
	{

	 return set.top();

	}

int Deck::size()
	{

	 return set.size();

	}
