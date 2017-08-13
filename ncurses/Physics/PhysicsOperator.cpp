
#include "Physics.cpp"
#include <ncurses.h>


using namespace std;


int main()
	{

	 initscr();
	 raw();

	 Physics base;
	 char key = ' ';

	 do{

	 base.update();
	 base.reflect();

	 mvprintw( 21, 0, "list of commands:");
	 mvprintw( 22, 0, "Add object: A" );
	 mvprintw( 23, 0,  "Remove object: R");
	 mvprintw( 24, 0,  "Quit Program: Q" );
	 mvprintw( 25, 0,  "Enter Command: " );

	 //get command
	 move( 25, 16);
	 timeout( 1000 );
	 key = getch();	 

	 //insert object
	 if( (key == 'A') || (key == 'a') )
		{

		 int xCor, yCor, digit = 10;
		 char toy;

		 mvprintw( 25, 0, "Enter character: " );
		
		 //receive character
		 do
		 {
		 timeout(-1);
		 move( 25, 17 );
		 toy = getch();
		 mvaddch( 25,17, ' ');
		 }while( ((toy<'a')&&(toy>'z')) || ((toy<'0')&&(toy>'9')) );

		 //get x coordinate
		 do{
		    xCor = 0;
		    mvprintw( 25, 0, "Enter x coordinate digits(0-49): ");

		    do
	   	      {
			  move(25, 34-digit/10);
			  key = getch();
			  if( key>='0' || key<='9' )
			     {

			      xCor += digit*(int(key-'0'));
			      digit/=10;

			     }
		      }while(digit!=0);//continue till last digit is reached
			 
		  digit = 10;	

		 }while( (xCor>=49) || (xCor<=0) );		


		 //get y coordinate
		 do{

		    yCor = 0;
		    mvprintw( 25, 0, "                                       ");

		    mvprintw( 25, 0, "Enter y coordinate digits(0-19): ");

		    do
	   	      {
			  move(25, (34-(digit/10)));
			  key = getch();
			  if( key>='0' || key<='9' )
			     {

			      yCor += digit*(int(key-'0'));
			      digit/=10;

			     }
		      }while(digit!=0);//continue till last digit is reached

		 digit = 10;
	
		 }while( (yCor>=19) || (yCor<=-1) );

		 mvprintw( 25, 0, "                                       ");		

		 base.addObject( toy, xCor, yCor);

		 //reset key pressed
		 key = ' ';
		}

	 base.gravity();

	 mvaddch( 25, 16, ' ');


	 }while( (key != 'q') && (key != 'Q') );

	 endwin();

	 return 0;

	}

