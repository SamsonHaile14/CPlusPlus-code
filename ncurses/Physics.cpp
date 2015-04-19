#include <cstdlib>
#include <vector>
#include <ctime>

#include <ncurses.h>

using namespace std;
//should be operated in full screen terminal

struct Object
	{

	 char image;
	 int xPoi;
	 int yPoi;

	};

class Physics
	{
	 public:
	 Physics();
	 ~Physics();
	 void reflect();
	 void update();
	 void addObject( char objectType, int xPlace, int yPlace );
	 void gravity();

	 //overwrite space with white space(or technically black space in terminal)
	 void removeObject( int xPlace, int yPlace );

	 private:
	 std::vector<char> element;
	 std::vector<Object> itemTable;
	 char* screen;
	 
	};

Physics::Physics()
	{
	 screen = new char[999];
         element.resize(999);

         for(int i = 0; i < 999; ++i)
             element[i] = ' ';

	 //top of box
	 for( int a = 0; a<49; a++)
	      element[a] = '-';

         //bottom of box
	 for( int a = 950; a<999; a++)
	      element[a] = '-';

	 for( int a = 1; a<19; a++)
	     {
	      //left side of box
	      element[50*(a)] = '|';

	      //right side of box
	      element[50*(a+1)-1] = '|';
	     }

	 update();
	 reflect();

	}

Physics::~Physics()
	{
	 delete[] screen;
	}

void Physics::update()
	{

	 for( int a = 0; a<999; a++)
	     screen[a] = element[a];

	}

void Physics::reflect()
	{

	 for(int a = 0; a< 20; a++)
		{
		 for(int b = 0; b< 50; b++)
			{
			 mvaddch( a, b, screen[b+50*a]);
			}
		}

	}

void Physics::addObject( char objectType, int xPlace, int yPlace )
	{
	 if( (xPlace < 50) && (yPlace < 20) )
		{
		 Object item;
		 item.image = objectType;
		 item.xPoi = xPlace;
		 item.yPoi = yPlace;
	
		 element[ xPlace + yPlace*50] = objectType;
		 itemTable.push_back( item );
		}
	} 

void Physics::removeObject( int xPlace, int yPlace )
	{
	 if( (xPlace < 50) && (yPlace < 20) )
		{

		 element[ xPlace + yPlace*50] = ' ';

		 for( int i = 0; i<itemTable.size(); i++)
			{
			 if( (xPlace == itemTable[i].xPoi) && 
						 (yPlace == itemTable[i].yPoi) )
				{
				 itemTable[i].xPoi = itemTable[itemTable.size() - 1].xPoi;
				 itemTable[i].yPoi = itemTable[itemTable.size() - 1].yPoi;
				 itemTable[i].image = itemTable[itemTable.size() - 1].image;
				 itemTable.pop_back();
				 break;
				}
			 			
			}


		}	 
	}

void Physics::gravity()
	{

	 for( int i = 0; i<itemTable.size(); i++ )
		{

		 if( element[ itemTable[i].xPoi + 50*(itemTable[i].yPoi+1) ] == ' ' )
			{

			 element[ itemTable[i].xPoi + 50*(itemTable[i].yPoi+1) ] = 
			 	itemTable[i].image;

			 element[itemTable[i].xPoi + 50*(itemTable[i].yPoi)] = ' '; 

		 	 itemTable[i].yPoi+=1;

			}

		}

	}
