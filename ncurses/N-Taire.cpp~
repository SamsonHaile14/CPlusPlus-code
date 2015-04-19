#include "Deck.cpp"
#include <ncurses.h>

using namespace std;

//function names
void titleScrn();
void setUpGame( Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		Deck suitPile[] );
void playGame(  Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		Deck suitPile[], Deck suitHide[] );
void moveCard(  Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		Deck suitPile[], Deck suitHide[] );
void unnaturalStates( Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		      Deck suitPile[], Deck suitHide[] );
void refreshScrn( Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		 Deck suitPile[] );

////////////////////////////////////////////////////////////////////////////////
int main()								      //
   {									      //
									      //
    Deck drawPile[3], cascadePile[8], cascadeHide[8], suitPile[4],suitHide[4];//
									      //
    initscr();								      //
    raw();								      //
									      //
    setUpGame(  drawPile, cascadePile, cascadeHide, suitPile );		      //
    playGame(  drawPile, cascadePile, cascadeHide, suitPile, suitHide );      //
									      //
    endwin();								      //
									      //
   }									      //
									      //
////////////////////////////////////////////////////////////////////////////////

//function stuff
void setUpGame(	 Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		 Deck suitPile[] )
   {

    drawPile[0].buildFullDeck();
    drawPile[0].shuffleDeck();

      for( int x = 0; x<8; x++ )	//setup hidden cascade piles
        {
         for( int y = 0; y<x; y++ )
	   drawPile[0].relocateTop( cascadeHide[x] );
	}

      for( int x = 0; x<8; x++ )	//setup cascade piles
         drawPile[0].relocateTop( cascadePile[x] );

    refreshScrn( drawPile, cascadePile, cascadeHide, suitPile );

    cascadePile[0].removeOutline(13,10,20,17);
    cascadePile[0].displayDeck(false, 13, 10, 20, 15);

   }

void playGame(  Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		Deck suitPile[], Deck suitHide[] )
   {

    char key;

//  mvaddstr( 34, 0, " To move cards, Press lowercase key corresponding to pile, and second number corresponding to destination" );
    do{

    mvaddstr( 35, 0, "Enter Selection:    " );
    move( 35, 17);
    key = getch();

    switch( key )
       {

	case 'D':

	   if( !drawPile[0].empty() )
	      {
	       drawPile[1].relocateTop(drawPile[2]);
	       drawPile[0].relocateTop(drawPile[1]);
 	      }

	   break;
		 
        case 'R':

	   drawPile[1].relocateTop( drawPile[0] );

	   while( !drawPile[2].empty() )
	      drawPile[2].relocateTop( drawPile[0] );

	   break;

	case 'Q':

	   while( (key != 'Y') && (key != 'N') )
	      {
	       mvaddstr( 37, 0, " Are you sure you want to quit? (Press Y for yes, N for no)     " );
	       move( 37, 61 );
	       key = getch();
	      }

	   if( key == 'Y' )//quit if user confirms
		  return;			

           mvaddstr( 37, 0, "                                                                 " );

	   break;

	case '#':
	   moveCard( drawPile, cascadePile, cascadeHide, suitPile, suitHide );

	break;

       }

    unnaturalStates( drawPile, cascadePile, cascadeHide, suitPile, suitHide );
    refreshScrn( drawPile, cascadePile, cascadeHide, suitPile );

    }while(true);

   }

////////////////////////////////////////////////////////////////////////////////

void moveCard(  Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		Deck suitPile[], Deck suitHide[] )
   {
    char srcDeck, destDeck;
    Deck* ptr;
    Deck extraCards;
    int count = 1;

    //receive input for source and destination decks
    mvaddstr( 37, 0, "Enter stack cards are to be removed from:");
    move( 37, 43 );
    echochar(' '); 
    srcDeck = getchar();
		 
    mvaddstr( 37, 0, "Enter stack cards are to be placed in:     ");
    move( 37, 44 );
    echochar(' '); 
    destDeck = getchar();

    mvaddstr( 37, 0, "                                            ");

    //determine stack cards are to be removed from
    if( (srcDeck >= 'a') && (srcDeck <= 'd' ) ) //foundation
       ptr = suitPile + ((int)(srcDeck-'a'));

    	else if( (srcDeck >= 'e') && (srcDeck <= 'l' ) ) //tableau
       	   ptr = cascadePile + ((int)(srcDeck-'e'));

    	else if( srcDeck == 'm' ) //draw pile
           ptr = drawPile+1;

    	else	//if not listed, no card is to be removed
           count = 0;

    //proceed with transfer process
    if( count == 0 )
       {
        mvaddstr(38,0,"invalid pile(s) selected");
	return;
       }
    	else if( ptr->empty() )
	   {
            mvaddstr( 38, 3, "No cards to pull from chosen pile");
	    return;
	   }
    	else if(destDeck == 'm')	//invalid destination of draw pile
	  { 
           mvaddstr(38,0,"cannot place card in draw pile area");
	   return;
	  }

    if( ((srcDeck>= 'e') && (srcDeck<='l')) && !( (destDeck>='a') && (destDeck<='d') ) )//determine # cards to be removed from the tableau
       {

        char value;
        count = 0;
        mvaddstr( 38, 3, "How many cards are to be removed from the tableau(enter two digits): ");
        move(38,69 );
        echochar(' '); 

        do{

        for( int a = 0; a<2; a++ ) //retrieve number of cards to be removed
	   {

	    do{

	    value = getchar();

	    if( ( (a==0)&&( (value!='0') && (value!='1') ) ) || ( (a==1) && ((value<'0')|| (value>'9')) ) )
	       {
	        mvaddstr(38,0,"invalid digit/number. Try again");
	        a = 0;
	        count = 0;
	       }

	    }while(( (a==0)&&( (value!='0') && (value!='1') ) ) || ( (a==1) && ((value<'0')|| (value>'9')) ));

	    count += (10-9*a )*((int)(value-'0'));

	   }

        }while( ptr->size() > count ); //repeat until acceptable count reached

        for( int x = 0; x<(count-1); x++ )
           ptr->relocateTop( extraCards );

       }

        if( (destDeck>= 'e') && (destDeck<='l') )	//destination is the tableau
           {

            string names[5] = {"Diamonds", "Spades", "Hearts", "Clubs", "Diamonds"};
            int color = 0;//0 = red, 1 = black

            for( int indx = 0; indx < 4; indx++ )//determine needed corresponding color
	       {

	        if( (cascadePile[ (int)(destDeck-'e') ].topInfo()).suit == names[indx])
	           color = indx % 2; 
	       }

             //moving king onto empty cascade
            if( ( cascadePile[ (int)(destDeck-'e') ].empty() ) &&  
	        ( (ptr->topInfo()).rank == 13 ) &&
	        ( cascadeHide[ (int)(destDeck-'e') ].empty() ) )
               {
	        ptr->relocateTop( cascadePile[ (int)(destDeck-'e') ] );
	       }
	
                //moving opposite color card of 1 less rank onto cascade
                else if( ( ( (ptr->topInfo()).suit == names[color+1] ) ||
		 	   ( (ptr->topInfo()).suit == names[color+3] ) ) &&  
			   ( ( (ptr->topInfo()).rank+1 ) == (cascadePile[ (int)(destDeck-'e') ].topInfo()).rank ) )
                   {
	            ptr->relocateTop( cascadePile[ (int)(destDeck-'e') ] );	
	           }

	        else
	           {
	            mvaddstr( 38, 3, "Invalid selection ");
	            count = 0;
	           }

	    if( count >1 ) //move rest of cards
	       {
	        for( int x = 0; x<(count-1);count++ )
		   extraCards.relocateTop( cascadePile[ (int)(destDeck-'e') ]);
	       }

	   }

	else if( (destDeck>='a') && (destDeck<='d') ) //destination is foundation
           {

            if( count > 1 )
	       mvaddstr( 38, 3, "Error: moving to many cards to the foundation ");		 
				 
                //if selected foundation is empty and src card has rank of 1, place src card on foundation
		else if( (  suitPile[ (int)(destDeck-'a') ].empty()  ) &&  ( (ptr->topInfo()).rank == 1 ) )
		   ptr->relocateTop( suitPile[ (int)(destDeck-'a') ] );

		//if selected foundation and src card suits match, and foundation rank is exactly one below src card, move card
		else if( ( ( (suitPile[ (int)(destDeck-'a') ].topInfo()).suit ) == ( (ptr->topInfo()).suit ) ) &&
	 	   	 ( (((ptr->topInfo()).rank) - 1) == ((suitPile[ (int)(destDeck-'a') ].topInfo()).rank)) )
		   {

		    suitPile[ (int)(destDeck-'a') ].relocateTop( suitHide[ (int)(destDeck-'a') ] );
		    ptr->relocateTop( suitPile[ (int)(destDeck-'a') ] );	
		   }

		else
		   {
		    mvaddstr( 38, 3, "Invalid selection ");
		    count = 0;
		   }

           }

    ptr = NULL;

   }

///////////////////////////////////////////////////////////////////////////////

void unnaturalStates( Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		      Deck suitPile[], Deck suitHide[] )
   {

    //visible foundation has no card, but corresponding invisible one does
    for( int x = 0; x<4; x++ )
      {

       if( suitPile[x].empty() )
	  suitHide[x].relocateTop( suitPile[x] );	    

      }

    //visible draw pile has no card, but corresponding invisible one does
    if( drawPile[1].empty() )
	drawPile[2].relocateTop( drawPile[1] );

   }

////////////////////////////////////////////////////////////////////////////////

void refreshScrn(Deck drawPile[], Deck cascadePile[], Deck cascadeHide[], 
		 Deck suitPile[] )
   {

    clear();

    int cPlace[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //assume displaced visible cascade

    //display screen layout
    mvaddstr( 30, 0, "Commands(in capital):" );
    mvaddstr( 31, 0, " D: Draw cards from drawpile " );
    mvaddstr( 32, 0, " R: Return drawn cards back to drawpile" );
    mvaddstr( 33, 0, " Q: Quit the game" );
    mvaddstr( 34, 0, " #: Move cards" );

    drawPile[0].displayDeck( true, 13, 10, 0, 0 );

    drawPile[1].displayDeck( false, 13, 10, 14, 0 ); 

    mvaddch(10,21,'m');

    for( int x = 0; x<4; x++ )
	{
 	 suitPile[x].displayDeck(false, 13, 10, 50+x*15, 0);
	 mvaddch(10, 57+15*x, ('a'+x)); 
	}

    for( int x = 0; x<8; x++ )
	{

	 if( !(cascadeHide[x].empty()) ) //don't display non-existent cards
	     cascadeHide[x].displayDeck(true, 13, 10, 20+x*15, 15);

	 else//displace actual cascade
	    cPlace[x] = 2;   

	}

    for( int x = 0; x<8; x++ )
	{
	 if( !cascadePile[x].empty() )
 	     cascadePile[x].displayDeck(false, 13, 10, 20+x*15, 17-cPlace[x]);
	 mvaddch(25+2*cascadePile[x].size(), 27+15*x, ('e'+x)); 
	}

   }
