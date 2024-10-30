#include "bass.h" 
#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "MemoryGame.h"

int delay=0; // for flipping cards back if the arent a identical

typedef struct
{
	int col;
	int row;
}cards;


cards card_place_pic1;
cards card_place_pic1_2;
cards card_place_pic2;
cards card_place_pic2_2;
cards card_place_pic3;
cards card_place_pic3_2;
cards card_place_pic4;
cards card_place_pic4_2;
cards card_place_pic5;
cards card_place_pic5_2;
cards card_place_pic6;
cards card_place_pic6_2;
cards card_place_pic7;
cards card_place_pic7_2;
cards card_place_pic8;
cards card_place_pic8_2;
cards card_place_pic9;
cards card_place_pic9_2;
cards card_place_pic10;
cards card_place_pic10_2;
cards card_place_pic11;
cards card_place_pic11_2;
cards card_place_pic12;
cards card_place_pic12_2;
cards card_place_pic13;
cards card_place_pic13_2;
cards card_place_pic14;
cards card_place_pic14_2;
cards card_place_pic15;
cards card_place_pic15_2;
cards card_place_pic16;
cards card_place_pic16_2;
cards card_place_pic17;
cards card_place_pic17_2;
cards card_place_pic18;
cards card_place_pic18_2;


/*
Point pic1;
Point pic1_2;
Point pic2;
Point pic2_2;
Point pic3;
Point pic3_2;
Point pic4;
Point pic4_2;
Point pic5;
Point pic5_2;
Point pic6;
Point pic6_2;
Point pic7;
Point pic7_2;
Point pic8;
Point pic8_2;
Point pic9;
Point pic9_2;
Point pic10;
Point pic10_2;
Point pic11;
Point pic11_2;
Point pic12;
Point pic12_2;
Point pic13;
Point pic13_2;
Point pic14;
Point pic14_2;
Point pic15;
Point pic15_2;
Point pic16;
Point pic16_2;
Point pic17;
Point pic17_2;
Point pic18;
Point pic1_2;
*/


cards card_temp_1;
cards card_temp_2;

HSTREAM card_flip_SND;
HSTREAM win_SND;
HSTREAM intro_SND;
HSTREAM gamingmusic_SND;
HSTREAM hmm_SND;

static int panelHandle, panelHandle_2, panelHandle_3, panelHandle_4;

//Random cards 
int random_num, rand_col, rand_row, programmer_rand_col_1=0,programmer_rand_row_1=0, programmer_rand_col_2=0,programmer_rand_row_2=0;
int pic1=0, pic2=0, pic3=0, pic4=0, pic5=0, pic6=0, pic7=0, pic8=0, pic9=0,
 pic10=0, pic11=0, pic12=0, pic13=0, pic14=0, pic15=0, pic16=0, pic17=0, pic18=0;
int game_col=100, game_row=100, game_col_1=100, game_row_1=100; 
int board[7][7]={{0}};
int programmer_board[7][7]={{0}};
Point board_array[36] = {{0}};
Point prog_array[36] = {{0}};

// counters and flags
int counter=0, counter_tries=0, counter_end=0;
int table_point=1, table_time=1, table_place=1, table_place_temp;
int load_row=0;
int flag_random=0, flag_match=0, flag_pause=0, flag_Stop = 0 ;

//Points
int point=3;

//calculate variables time
int counter_game_time=0, dt=50, temp_time=0;


int card_pic1, card_pic2, card_pic3, card_pic4, card_pic5, card_pic6, card_pic7, card_pic8, card_pic9,
 card_pic10, card_pic11, card_pic12, card_pic13, card_pic14, card_pic15, card_pic16, card_pic17, card_pic18;
int cover;


int rows=6, cols=6;
int box=90;


char record_table[100];
char players[1000];
int points[500]={{0}}, times[500]={{0}}; 
int game_mode = 0 ; // regular mode - game_mode == 0 , programmer mode - game_mode == 1 


void initialize();
void terminate();
void turn_cards_back();
void game_time();
void NextModefunc();
//void pair_random();
void mouse_click();
void random();
void flip_card();
void check_same_card();
void win_condition();
void write_record_file();
void read_record_file();

int main (int argc, char *argv[])
{
	srand(time(0));
	
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "MemoryGame.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle_2 = LoadPanel (0, "MemoryGame.uir", PANEL_2)) < 0)
		return -1;
	if ((panelHandle_3 = LoadPanel (0, "MemoryGame.uir", PANEL_3)) < 0)
		return -1;
	if ((panelHandle_4 = LoadPanel (0, "MemoryGame.uir", PANEL_4)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	
	initialize();
	
	RunUserInterface ();
	
	terminate();
	
	DiscardPanel (panelHandle);
	DiscardPanel (panelHandle_2);
	DiscardPanel (panelHandle_3);
	DiscardPanel (panelHandle_4);
	return 0;
}

void InitMP3s(void)
{
	BASS_Init( -1,44100, 0,0,NULL); 
	card_flip_SND = BASS_StreamCreateFile(FALSE,"card_flip.mp3",0,0,0);
	win_SND = BASS_StreamCreateFile(FALSE,"win.mp3",0,0,0);
	intro_SND = BASS_StreamCreateFile(FALSE,"intro.mp3",0,0,0);
	gamingmusic_SND = BASS_StreamCreateFile(FALSE,"gamingmusic.mp3",0,0,0);
	hmm_SND = BASS_StreamCreateFile(FALSE,"hmm.mp3",0,0,0);
}

void ReleaseMP3s(void)
{
	 BASS_StreamFree(card_flip_SND);
	 BASS_StreamFree(win_SND);
	 BASS_StreamFree(intro_SND);
	 BASS_StreamFree(gamingmusic_SND);
	 BASS_StreamFree(hmm_SND);
}

void initialize()
{
	read_record_file();
	
	InitMP3s();
	BASS_ChannelPlay(intro_SND,TRUE);
	
	GetBitmapFromFile ("pictures//cover.png", &cover);
	GetBitmapFromFile ("pictures//pic1.png", &card_pic1);
	GetBitmapFromFile ("pictures//pic2.png", &card_pic2);
	GetBitmapFromFile ("pictures//pic3.png", &card_pic3);
	GetBitmapFromFile ("pictures//pic4.png", &card_pic4);
	GetBitmapFromFile ("pictures//pic5.png", &card_pic5);
	GetBitmapFromFile ("pictures//pic6.png", &card_pic6);
	GetBitmapFromFile ("pictures//pic7.png", &card_pic7);
	GetBitmapFromFile ("pictures//pic8.png", &card_pic8);
	GetBitmapFromFile ("pictures//pic9.png", &card_pic9);
	GetBitmapFromFile ("pictures//pic10.png", &card_pic10);
	GetBitmapFromFile ("pictures//pic11.png", &card_pic11);
	GetBitmapFromFile ("pictures//pic12.png", &card_pic12);
	GetBitmapFromFile ("pictures//pic13.png", &card_pic13);
	GetBitmapFromFile ("pictures//pic14.png", &card_pic14);
	GetBitmapFromFile ("pictures//pic15.png", &card_pic15);
	GetBitmapFromFile ("pictures//pic16.png", &card_pic16);
	GetBitmapFromFile ("pictures//pic17.png", &card_pic17);
	GetBitmapFromFile ("pictures//pic18.png", &card_pic18);


	turn_cards_back();
}

void terminate()
{
	ReleaseMP3s();
	
	DiscardBitmap(cover);
	DiscardBitmap(card_pic1);
	DiscardBitmap(card_pic2);
	DiscardBitmap(card_pic3);
	DiscardBitmap(card_pic4);
	DiscardBitmap(card_pic5);
	DiscardBitmap(card_pic6);
	DiscardBitmap(card_pic7);
	DiscardBitmap(card_pic8);
	DiscardBitmap(card_pic9);
	DiscardBitmap(card_pic10);
	DiscardBitmap(card_pic11);
	DiscardBitmap(card_pic12);
	DiscardBitmap(card_pic13);
	DiscardBitmap(card_pic14);
	DiscardBitmap(card_pic15);
	DiscardBitmap(card_pic16);
	DiscardBitmap(card_pic17);
	DiscardBitmap(card_pic18);
}

int CVICALLBACK PanelFunc (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:
			SetMouseCursor (VAL_POINTING_FINGER_CURSOR);

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK PanelFunc_2 (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:
			BASS_ChannelPlay(gamingmusic_SND,TRUE);

			break;
		case EVENT_LOST_FOCUS:

			break;
			
		case EVENT_CLOSE:
			
			HidePanel (panelHandle_2);
			BASS_ChannelPlay(intro_SND,TRUE);
			BASS_ChannelStop(gamingmusic_SND);
			flag_pause=1;
			SetCtrlAttribute (panelHandle_2, PANEL_2_TIMER, ATTR_ENABLED, 0);
			SetCtrlAttribute (panelHandle, PANEL_RESETBUTTON, ATTR_VISIBLE, 1);
			break;
	}
	return 0;
}

int CVICALLBACK PanelFunc_3 (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (panelHandle_3);
			break;
	}
	return 0;
}

int CVICALLBACK PanelFunc_4 (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (panelHandle_4);
			break;
	}
	return 0;
}

void turn_cards_back()
{
	CanvasStartBatchDraw (panelHandle_2, PANEL_2_CANVAS);
	
	for(int i=0 ; i<6 ; i++)
		for(int j=0 ; j<6 ; j++)
		{
			CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, cover, VAL_ENTIRE_OBJECT, MakeRect(90*i,90*j,90,90));
		}
	
	CanvasEndBatchDraw (panelHandle_2, PANEL_2_CANVAS);
}

int CVICALLBACK NameFunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (panelHandle_2, PANEL_2_NAME_STRING, &players[table_place-1]);
			SetTableCellVal (panelHandle_3, PANEL_3_TABLE,  MakePoint (1,table_place), &players[table_place-1]);
			
			table_place++;
			
			SetCtrlAttribute (panelHandle_2, PANEL_2_NAME_STRING, ATTR_DIMMED, 1);
			SetCtrlAttribute (panelHandle_2, PANEL_2_CANVAS, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle_2, PANEL_2_TIMER, ATTR_ENABLED, 1);
			
			break;
	}
	return 0;
}

int CVICALLBACK StartButtonFunc (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			BASS_ChannelStop(intro_SND);
			BASS_ChannelPlay(gamingmusic_SND,TRUE);
			
			DisplayPanel (panelHandle_2);
			if(counter_game_time == 0)
			{	if(flag_random == 0) //only for pics that didnt get into the cards map
				{
			   		random();
				}
				MessagePopup("Hear me out","To start play,\n please enter your name\n and than press Enter");
			}
			
			if(flag_pause==1)
				SetCtrlAttribute (panelHandle_2, PANEL_2_TIMER, ATTR_ENABLED, 1);
			
			break;
			
	}
	return 0;
}

int CVICALLBACK ResetFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			for(int i=0 ; i<6 ;i++)
				for(int j=0 ; j<6 ; j++)
					board[i][j]=0;
			
			table_point++;
			table_time++;
			
			counter=0;
			counter_game_time=0;
			counter_tries=0;
			counter_end=0;
			flag_random=0;
			flag_match=0;
			point=3;
			game_mode = 0 ;
			
			turn_cards_back();
			
			SetCtrlVal (panelHandle_2, PANEL_2_SCORE, point);
			SetCtrlAttribute (panelHandle_2, PANEL_2_NAME_STRING, ATTR_DIMMED, 0);
			SetCtrlAttribute (panelHandle_2, PANEL_2_CANVAS, ATTR_DIMMED, 1);
			SetCtrlAttribute (panelHandle_2, PANEL_2_TIMER, ATTR_ENABLED, 0);
			
			break;
	}
	return 0;
}

int CVICALLBACK RecordButton (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			DisplayPanel (panelHandle_3);

			break;
	}
	return 0;
}

int CVICALLBACK AboutButton (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			DisplayPanel (panelHandle_4);

			break;
	}
	return 0;
}

void game_time() // timer on board
{
	SetCtrlVal (panelHandle_2, PANEL_2_TIME, counter_game_time/dt);
	
	counter_game_time++;
}

void CVICALLBACK MenuHelpFunc (int menuBar, int menuItem, void *callbackData,
							   int panel)
{
	switch(panel)
	{
		case EVENT_COMMIT:
			
			BASS_ChannelStop(intro_SND);
			OpenDocumentInDefaultViewer ("Help.pdf", VAL_NO_ZOOM);
			
			break;
	}
}

void CVICALLBACK MenuDemoFunc (int menuBar, int menuItem, void *callbackData,
							   int panel)
{
	 BASS_ChannelStop(intro_SND);
	 OpenDocumentInDefaultViewer ("Video.mp4", VAL_MAXIMIZE);
}

int CVICALLBACK TimerFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			game_time();
			
			/*
			// while player playing on programmer mode
			if (game_mode == 1)
			{
				if((counter_game_time/dt) % 5 == 0)
				{
					pair_random();
				}	
			}		
			*/
		
			
			
			
			
			break;
	}
	return 0;
}

int CVICALLBACK Delayfunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			if(flag_match == 0 && counter == 2 ) //for two cards that are open and arent the same - close them
				{	
					BASS_ChannelPlay(hmm_SND,TRUE);		
					for(delay ; delay < 100000001 ; delay++) // make the delay after wrong pair flipped 
					{
						flag_Stop = 1 ;
						if (delay == 100000000 )
						{
							CanvasStartBatchDraw (panelHandle_2, PANEL_2_CANVAS);
							CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, cover, VAL_ENTIRE_OBJECT,
											  MakeRect(90*(card_temp_1.row),90*(card_temp_1.col),90,90));
							CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, cover, VAL_ENTIRE_OBJECT,
											  MakeRect(90*(card_temp_2.row),90*(card_temp_2.col),90,90));	
									
							game_row_1 = 8 ; // make sure that these veriables wont get junk value in the array.
							game_col_1 = 8 ;	
						}
					}	
					delay = 0 ;
					counter = 0 ;
					flag_Stop = 0 ;
				}			

			break;
	}
	return 0;
}

void mouse_click()
{

	 if(counter == 0 || counter == 1 )
	 {
		 static int x = 0, y = 0;
	
		 counter_tries++; // count moves
			
				if(counter_tries == 12) // minus 1 points for every 12 clicks which mean 6 turns of card pairs clicking
				{
					if(point > 0)
					{
						point--;
						SetCtrlVal (panelHandle_2, PANEL_2_SCORE, point);
					}
					counter_tries = 0;
				}
			
				if(counter < 2) // can click only two times for pick cards every turn
				{
					GetRelativeMouseState (panelHandle_2, PANEL_2_CANVAS, &x, &y, 0, 0, 0);
					if(delay != 0 || flag_Stop != 0)
					{
						x = 0 , y = 0 ;
					}
					game_col = x/box;
					game_row = y/box;
				
					if(board[game_col][game_row] < 2) // player is not allowed to flip open card that has a couple already
					{
						if(game_col != game_col_1 || game_row != game_row_1) //prevent the player to press the same card
								{
									BASS_ChannelPlay(card_flip_SND,TRUE);
									counter++; // number of clicks	
					
									game_col_1 = game_col;
									game_row_1 = game_row;
					
									if(counter == 1) //first card
									{
									card_temp_1.row = game_row_1;
								    card_temp_1.col = game_col_1;
									flip_card();
									}
					
									if(counter == 2) //second card 
									{
									card_temp_2.row = game_row_1;
								    card_temp_2.col = game_col_1;
									flip_card();
									check_same_card();
									}
								}
					}
				}
	 }
}

int CVICALLBACK CanvasFunc (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	CanvasStartBatchDraw (panelHandle_2, PANEL_2_CANVAS);
	
	switch(event)
	{
		case EVENT_LEFT_CLICK:
			mouse_click();
			break;
	}
	
	CanvasEndBatchDraw (panelHandle_2, PANEL_2_CANVAS);
	
	return 0;
}

void flip_card()
{
	
	if(card_place_pic1.col == game_col_1  && card_place_pic1.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic1, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic1.row), 90*(card_place_pic1.col),90,90));		
	
	if(card_place_pic2.col == game_col_1  && card_place_pic2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic2, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic2.row), 90*(card_place_pic2.col),90,90));		
	
	if(card_place_pic3.col == game_col_1  && card_place_pic3.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic3, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic3.row), 90*(card_place_pic3.col),90,90));		
	
	if(card_place_pic4.col == game_col_1  && card_place_pic4.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic4, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic4.row), 90*(card_place_pic4.col),90,90));		
	
	if(card_place_pic5.col == game_col_1  && card_place_pic5.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic5, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic5.row), 90*(card_place_pic5.col),90,90));		
	
	if(card_place_pic6.col == game_col_1  && card_place_pic6.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic6, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic6.row), 90*(card_place_pic6.col),90,90));		
	
	if(card_place_pic7.col == game_col_1  && card_place_pic7.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic7, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic7.row), 90*(card_place_pic7.col),90,90));		
	
	if(card_place_pic8.col == game_col_1  && card_place_pic8.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic8, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic8.row), 90*(card_place_pic8.col),90,90));		
	
	if(card_place_pic9.col == game_col_1  && card_place_pic9.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic9, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic9.row), 90*(card_place_pic9.col),90,90));		
	
	if(card_place_pic10.col == game_col_1  && card_place_pic10.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic10, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic10.row), 90*(card_place_pic10.col),90,90));		
	
	if(card_place_pic11.col == game_col_1  && card_place_pic11.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic11, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic11.row), 90*(card_place_pic11.col),90,90));		
	
	if(card_place_pic12.col == game_col_1  && card_place_pic12.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic12, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic12.row), 90*(card_place_pic12.col),90,90));		
	
	if(card_place_pic13.col == game_col_1  && card_place_pic13.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic13, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic13.row), 90*(card_place_pic13.col),90,90));		
	
	if(card_place_pic14.col == game_col_1  && card_place_pic14.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic14, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic14.row), 90*(card_place_pic14.col),90,90));		
	
	if(card_place_pic15.col == game_col_1  && card_place_pic15.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic15, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic15.row), 90*(card_place_pic15.col),90,90));		
	
	if(card_place_pic16.col == game_col_1  && card_place_pic16.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic16, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic16.row), 90*(card_place_pic16.col),90,90));		
	
	if(card_place_pic17.col == game_col_1  && card_place_pic17.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic17, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic17.row), 90*(card_place_pic17.col),90,90));		
	
	if(card_place_pic18.col == game_col_1  && card_place_pic18.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic18, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic18.row), 90*(card_place_pic18.col),90,90));		
	
	
	
	if(card_place_pic1_2.col == game_col_1  && card_place_pic1_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic1, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic1_2.row), 90*(card_place_pic1_2.col),90,90));		
	
	if(card_place_pic2_2.col == game_col_1  && card_place_pic2_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic2, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic2_2.row), 90*(card_place_pic2_2.col),90,90));
	
	if(card_place_pic3_2.col == game_col_1  && card_place_pic3_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic3, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic3_2.row), 90*(card_place_pic3_2.col),90,90));
	
	if(card_place_pic4_2.col == game_col_1  && card_place_pic4_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic4, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic4_2.row), 90*(card_place_pic4_2.col),90,90));
	
	if(card_place_pic5_2.col == game_col_1  && card_place_pic5_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic5, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic5_2.row), 90*(card_place_pic5_2.col),90,90));	
	
	if(card_place_pic6_2.col == game_col_1  && card_place_pic6_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic6, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic6_2.row), 90*(card_place_pic6_2.col),90,90));		
	
	if(card_place_pic7_2.col == game_col_1  && card_place_pic7_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic7, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic7_2.row), 90*(card_place_pic7_2.col),90,90));
	
	if(card_place_pic8_2.col == game_col_1  && card_place_pic8_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic8, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic8_2.row), 90*(card_place_pic8_2.col),90,90));		
	
	if(card_place_pic9_2.col == game_col_1  && card_place_pic9_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic9, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic9_2.row), 90*(card_place_pic9_2.col),90,90));	
	
	if(card_place_pic10_2.col == game_col_1  && card_place_pic10_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic10, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic10_2.row), 90*(card_place_pic10_2.col),90,90));		
	
	if(card_place_pic11_2.col == game_col_1  && card_place_pic11_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic11, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic11_2.row), 90*(card_place_pic11_2.col),90,90));
	
	if(card_place_pic12_2.col == game_col_1  && card_place_pic12_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic12, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic12_2.row), 90*(card_place_pic12_2.col),90,90));		
	
	if(card_place_pic13_2.col == game_col_1  && card_place_pic13_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic13, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic13_2.row), 90*(card_place_pic13_2.col),90,90));	
	
	if(card_place_pic14_2.col == game_col_1  && card_place_pic14_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic14, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic14_2.row), 90*(card_place_pic14_2.col),90,90));		
	
	if(card_place_pic15_2.col == game_col_1  && card_place_pic15_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic15, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic15_2.row), 90*(card_place_pic15_2.col),90,90));
	
	if(card_place_pic16_2.col == game_col_1  && card_place_pic16_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic16, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic16_2.row), 90*(card_place_pic16_2.col),90,90));		
	
	if(card_place_pic17_2.col == game_col_1  && card_place_pic17_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic17, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic17_2.row), 90*(card_place_pic17_2.col),90,90));
	
	if(card_place_pic18_2.col == game_col_1  && card_place_pic18_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_pic18, VAL_ENTIRE_OBJECT,
						  MakeRect(90*(card_place_pic18_2.row), 90*(card_place_pic18_2.col),90,90));
	
}

void random()
{
	while(flag_random == 0)
	{
		random_num = 1 + rand()%18; // choose card

		if(flag_random == 0) // check if need more random function 
		{
			if (random_num == 1 && pic1 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic1==0) 
					{
						card_place_pic1.col = rand_col-1;
						card_place_pic1.row = rand_row-1;
						//prog_array[0] = card_place_pic1;
					}
					
					if(pic1==1) 
					{
						card_place_pic1_2.col = rand_col-1;
						card_place_pic1_2.row = rand_row-1;
						//prog_array[1] = card_place_pic1_2;
					}
					
					pic1++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic2 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic2==0) 
					{
						card_place_pic2.col = rand_col-1;
						card_place_pic2.row = rand_row-1;
						//prog_array[2] = card_place_pic2;
					}
					
					if(pic2==1) 
					{
						card_place_pic2_2.col = rand_col-1;
						card_place_pic2_2.row = rand_row-1;
						//prog_array[3] = card_place_pic2_2;
					}
					
					pic2++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic3 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic3==0) 
					{
						card_place_pic3.col = rand_col-1;
						card_place_pic3.row = rand_row-1;
						//prog_array[4] = card_place_pic3;
					}
					
					if(pic3==1) 
					{
						card_place_pic3_2.col = rand_col-1;
						card_place_pic3_2.row = rand_row-1;
						//prog_array[5] = card_place_pic3_2;
					}
					
					pic3++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic4 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic4==0) 
					{
						card_place_pic4.col = rand_col-1;
						card_place_pic4.row = rand_row-1;
						//prog_array[6] = card_place_pic4;
					}
					
					if(pic4==1) 
					{
						card_place_pic4_2.col = rand_col-1;
						card_place_pic4_2.row = rand_row-1;
						//prog_array[7] = card_place_pic4_2;
					}
					
					pic4++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic5 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic5==0) 
					{
						card_place_pic5.col = rand_col-1;
						card_place_pic5.row = rand_row-1;
						//prog_array[8] = card_place_pic5;
					}
					
					if(pic5==1) 
					{
						card_place_pic5_2.col = rand_col-1;
						card_place_pic5_2.row = rand_row-1;
						//prog_array[9] = card_place_pic5_2;
					}
					
					pic5++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic6 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic6==0) 
					{
						card_place_pic6.col = rand_col-1;
						card_place_pic6.row = rand_row-1;
						//prog_array[10] = card_place_pic6;
					}
					
					if(pic6==1) 
					{
						card_place_pic6_2.col = rand_col-1;
						card_place_pic6_2.row = rand_row-1;
						//prog_array[11] = card_place_pic6_2;
					}
					
					pic6++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic7 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic7==0) 
					{
						card_place_pic7.col = rand_col-1;
						card_place_pic7.row = rand_row-1;
						//prog_array[12] = card_place_pic7;
					}
					
					if(pic7==1) 
					{
						card_place_pic7_2.col = rand_col-1;
						card_place_pic7_2.row = rand_row-1;
						//prog_array[13] = card_place_pic7_2;
					}
					
					pic7++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic8 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic8==0) 
					{
						card_place_pic8.col = rand_col-1;
						card_place_pic8.row = rand_row-1;
						//prog_array[14] = card_place_pic8;
					}
					
					if(pic8==1) 
					{
						card_place_pic8_2.col = rand_col-1;
						card_place_pic8_2.row = rand_row-1;
						//prog_array[15] = card_place_pic8_2;
					}
					
					pic8++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic9 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic9==0) 
					{
						card_place_pic9.col = rand_col-1;
						card_place_pic9.row = rand_row-1;
						//prog_array[16] = card_place_pic9;
					}
					
					if(pic9==1) 
					{
						card_place_pic9_2.col = rand_col-1;
						card_place_pic9_2.row = rand_row-1;
						//prog_array[17] = card_place_pic9_2;
					}
					
					pic9++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic10 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic10==0) 
					{
						card_place_pic10.col = rand_col-1;
						card_place_pic10.row = rand_row-1;
						//prog_array[18] = card_place_pic10;
					}
					
					if(pic10==1) 
					{
						card_place_pic10_2.col = rand_col-1;
						card_place_pic10_2.row = rand_row-1;
						//prog_array[19] = card_place_pic10_2;
					}
					
					pic10++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic11 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic11==0) 
					{
						card_place_pic11.col = rand_col-1;
						card_place_pic11.row = rand_row-1;
						//prog_array[20] = card_place_pic11;
					}
					
					if(pic11==1) 
					{
						card_place_pic11_2.col = rand_col-1;
						card_place_pic11_2.row = rand_row-1;
						//prog_array[21] = card_place_pic11_2;
					}
					
					pic11++; // number of cards with the same name is on the board.
				}
			}

			if (random_num == 1 && pic12 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic12==0) 
					{
						card_place_pic12.col = rand_col-1;
						card_place_pic12.row = rand_row-1;
						//prog_array[22] = card_place_pic12;
					}
					
					if(pic12==1) 
					{
						card_place_pic12_2.col = rand_col-1;
						card_place_pic12_2.row = rand_row-1;
						//prog_array[23] = card_place_pic12_2;
					}
					
					pic12++; // number of cards with the same name is on the board.
				}
			}
			
			if (random_num == 1 && pic13 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic13==0) 
					{
						card_place_pic13.col = rand_col-1;
						card_place_pic13.row = rand_row-1;
						//prog_array[24] = card_place_pic13;
					}
					
					if(pic13==1) 
					{
						card_place_pic13_2.col = rand_col-1;
						card_place_pic13_2.row = rand_row-1;
						//prog_array[25] = card_place_pic13_2;
					}
					
					pic13++; // number of cards with the same name is on the board.
				}
			}
			
			if (random_num == 1 && pic14 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic14==0) 
					{
						card_place_pic14.col = rand_col-1;
						card_place_pic14.row = rand_row-1;
						//prog_array[26] = card_place_pic14;
					}
					
					if(pic14==1) 
					{
						card_place_pic14_2.col = rand_col-1;
						card_place_pic14_2.row = rand_row-1;
						//prog_array[27] = card_place_pic14_2;
					}
					
					pic14++; // number of cards with the same name is on the board.
				}
			}
			
			if (random_num == 1 && pic15 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic15==0) 
					{
						card_place_pic15.col = rand_col-1;
						card_place_pic15.row = rand_row-1;
						//prog_array[28] = card_place_pic15;
					}
					
					if(pic15==1) 
					{
						card_place_pic15_2.col = rand_col-1;
						card_place_pic15_2.row = rand_row-1;
						//prog_array[29] = card_place_pic15_2;
					}
					
					pic15++; // number of cards with the same name is on the board.
				}
			}
			
			if (random_num == 1 && pic16< 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic16==0) 
					{
						card_place_pic16.col = rand_col-1;
						card_place_pic16.row = rand_row-1;
						//prog_array[30] = card_place_pic16;
					}
					
					if(pic16==1) 
					{
						card_place_pic16_2.col = rand_col-1;
						card_place_pic16_2.row = rand_row-1;
						//prog_array[31] = card_place_pic16_2;
					}
					
					pic16++; // number of cards with the same name is on the board.
				}
			}
			
			if (random_num == 1 && pic17 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic17==0) 
					{
						card_place_pic17.col = rand_col-1;
						card_place_pic17.row = rand_row-1;
						//prog_array[32] = card_place_pic17;
					}
					
					if(pic17==1) 
					{
						card_place_pic17_2.col = rand_col-1;
						card_place_pic17_2.row = rand_row-1;
						//prog_array[33] = card_place_pic17_2;
					}
					
					pic17++; // number of cards with the same name is on the board.
				}
			}
			
			if (random_num == 1 && pic18 < 2) 
			{
	            if(point<18)
				{
					rand_col = 1 + rand()%6; //random place on col
					rand_row = 1 + rand()%6; //random place on row
				}
				if (board[rand_col][rand_row] == 0) // if the random place is with card or not
				{
					board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
					
					if(pic18==0) 
					{
						card_place_pic18.col = rand_col-1;
						card_place_pic18.row = rand_row-1;
						//prog_array[34] = card_place_pic18;
					}
					
					if(pic18==1) 
					{
						card_place_pic18_2.col = rand_col-1;
						card_place_pic18_2.row = rand_row-1;
						//prog_array[35] = card_place_pic18_2;
					}
					
					pic18++; // number of cards with the same name is on the board.
				}
			}
		
		if(pic1==2 && pic2==2 && pic3==2 && pic4==2 && pic5==2 && pic6==2 && pic7==2 && pic8==2 &&
				pic9==2 && pic10==2 && pic11==2 && pic12==2 && pic13==2
				&& pic14==2 && pic15==2 && pic16==2 && pic17==2 && pic18==2)
			flag_random=1;
		}
	}	
}

void check_same_card()
{
	flag_match=0;									 
	
	if((card_temp_1.row == card_place_pic1.row) && (card_temp_1.col == card_place_pic1.col))
	{
		if((card_temp_2.row == card_place_pic1_2.row) && (card_temp_2.col == card_place_pic1_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic1_2.row) && (card_temp_1.col == card_place_pic1_2.col))
	{
		if((card_temp_2.row == card_place_pic1.row) && (card_temp_2.col == card_place_pic1.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic2.row) && (card_temp_1.col == card_place_pic2.col))
	{
		if((card_temp_2.row == card_place_pic2_2.row) && (card_temp_2.col == card_place_pic2_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic2_2.row) && (card_temp_1.col == card_place_pic2_2.col))
	{
		if((card_temp_2.row == card_place_pic2.row) && (card_temp_2.col == card_place_pic2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic3.row) && (card_temp_1.col == card_place_pic3.col))
	{
		if((card_temp_2.row == card_place_pic3_2.row) && (card_temp_2.col == card_place_pic3_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic3_2.row) && (card_temp_1.col == card_place_pic3_2.col))
	{
		if((card_temp_2.row == card_place_pic3.row) && (card_temp_2.col == card_place_pic3.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic4.row) && (card_temp_1.col == card_place_pic4.col))
	{
		if((card_temp_2.row == card_place_pic4_2.row) && (card_temp_2.col == card_place_pic4_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic4_2.row) && (card_temp_1.col == card_place_pic4_2.col))
	{
		if((card_temp_2.row == card_place_pic4.row) && (card_temp_2.col == card_place_pic4.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic5.row) && (card_temp_1.col == card_place_pic5.col))
	{
		if((card_temp_2.row == card_place_pic5_2.row) && (card_temp_2.col == card_place_pic5_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic5_2.row) && (card_temp_1.col == card_place_pic5_2.col))
	{
		if((card_temp_2.row == card_place_pic5.row) && (card_temp_2.col == card_place_pic5.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic6.row) && (card_temp_1.col == card_place_pic6.col))
	{
		if((card_temp_2.row == card_place_pic6_2.row) && (card_temp_2.col == card_place_pic6_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic6_2.row) && (card_temp_1.col == card_place_pic6_2.col))
	{
		if((card_temp_2.row == card_place_pic6.row) && (card_temp_2.col == card_place_pic6.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic7.row) && (card_temp_1.col == card_place_pic7.col))
	{
		if((card_temp_2.row == card_place_pic7_2.row) && (card_temp_2.col == card_place_pic7_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic7_2.row) && (card_temp_1.col == card_place_pic7_2.col))
	{
		if((card_temp_2.row == card_place_pic7.row) && (card_temp_2.col == card_place_pic7.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	
	if((card_temp_1.row == card_place_pic8.row) && (card_temp_1.col == card_place_pic8.col))
	{
		if((card_temp_2.row == card_place_pic8_2.row) && (card_temp_2.col == card_place_pic8_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic8_2.row) && (card_temp_1.col == card_place_pic8_2.col))
	{
		if((card_temp_2.row == card_place_pic8.row) && (card_temp_2.col == card_place_pic8.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	
	
	if((card_temp_1.row == card_place_pic9.row) && (card_temp_1.col == card_place_pic9.col))
	{
		if((card_temp_2.row == card_place_pic9_2.row) && (card_temp_2.col == card_place_pic9_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic9_2.row) && (card_temp_1.col == card_place_pic9_2.col))
	{
		if((card_temp_2.row == card_place_pic9.row) && (card_temp_2.col == card_place_pic9.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	
	if((card_temp_1.row == card_place_pic10.row) && (card_temp_1.col == card_place_pic10.col))
	{
		if((card_temp_2.row == card_place_pic10_2.row) && (card_temp_2.col == card_place_pic10_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic10_2.row) && (card_temp_1.col == card_place_pic10_2.col))
	{
		if((card_temp_2.row == card_place_pic10.row) && (card_temp_2.col == card_place_pic10.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	
	if((card_temp_1.row == card_place_pic11.row) && (card_temp_1.col == card_place_pic11.col))
	{
		if((card_temp_2.row == card_place_pic11_2.row) && (card_temp_2.col == card_place_pic11_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic11_2.row) && (card_temp_1.col == card_place_pic11_2.col))
	{
		if((card_temp_2.row == card_place_pic11.row) && (card_temp_2.col == card_place_pic11.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	
	if((card_temp_1.row == card_place_pic12.row) && (card_temp_1.col == card_place_pic12.col))
	{
		if((card_temp_2.row == card_place_pic12_2.row) && (card_temp_2.col == card_place_pic12_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic12_2.row) && (card_temp_1.col == card_place_pic12_2.col))
	{
		if((card_temp_2.row == card_place_pic12.row) && (card_temp_2.col == card_place_pic12.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic13.row) && (card_temp_1.col == card_place_pic13.col))
	{
		if((card_temp_2.row == card_place_pic13_2.row) && (card_temp_2.col == card_place_pic13_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic13_2.row) && (card_temp_1.col == card_place_pic13_2.col))
	{
		if((card_temp_2.row == card_place_pic13.row) && (card_temp_2.col == card_place_pic13.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	if((card_temp_1.row == card_place_pic14.row) && (card_temp_1.col == card_place_pic14.col))
	{
		if((card_temp_2.row == card_place_pic14_2.row) && (card_temp_2.col == card_place_pic14_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic14_2.row) && (card_temp_1.col == card_place_pic14_2.col))
	{
		if((card_temp_2.row == card_place_pic14.row) && (card_temp_2.col == card_place_pic14.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic15.row) && (card_temp_1.col == card_place_pic15.col))
	{
		if((card_temp_2.row == card_place_pic15_2.row) && (card_temp_2.col == card_place_pic15_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic15_2.row) && (card_temp_1.col == card_place_pic15_2.col))
	{
		if((card_temp_2.row == card_place_pic15.row) && (card_temp_2.col == card_place_pic15.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic16.row) && (card_temp_1.col == card_place_pic16.col))
	{
		if((card_temp_2.row == card_place_pic16_2.row) && (card_temp_2.col == card_place_pic16_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic16_2.row) && (card_temp_1.col == card_place_pic16_2.col))
	{
		if((card_temp_2.row == card_place_pic16.row) && (card_temp_2.col == card_place_pic16.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic17.row) && (card_temp_1.col == card_place_pic17.col))
	{
		if((card_temp_2.row == card_place_pic17_2.row) && (card_temp_2.col == card_place_pic17_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic17_2.row) && (card_temp_1.col == card_place_pic17_2.col))
	{
		if((card_temp_2.row == card_place_pic17.row) && (card_temp_2.col == card_place_pic17.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic18.row) && (card_temp_1.col == card_place_pic18.col))
	{
		if((card_temp_2.row == card_place_pic18_2.row) && (card_temp_2.col == card_place_pic18_2.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	if((card_temp_1.row == card_place_pic18_2.row) && (card_temp_1.col == card_place_pic18_2.col))
	{
		if((card_temp_2.row == card_place_pic18.row) && (card_temp_2.col == card_place_pic18.col))
		{
			flag_match=1;
			counter=0;
			if(game_mode == 1 )
			{	
				programmer_board[card_temp_1.col][card_temp_1.row]=1;
				programmer_board[card_temp_2.col][card_temp_2.row]=1;
			}
		}
	}
	
	
	
	if(flag_match==1)
	{
		BASS_ChannelPlay(win_SND,TRUE);
		
		point++;
		
		SetCtrlVal (panelHandle_2, PANEL_2_SCORE, point);
		
		board[card_temp_1.col][card_temp_1.row]=2;
		board[card_temp_2.col][card_temp_2.row]=2;
		
		win_condition();
		
		counter_tries=0;
	}
}

void NextModefunc()
{
	for(int i=0 ; i<6 ;i++)
		for(int j=0 ; j<6 ; j++)
			board[i][j]=0;
			
	table_point++;
	table_time++;
	
	counter=0;
	counter_game_time=0;
	counter_tries=0;
	counter_end=0;
	flag_random=0;
	flag_match=0;
	point=5;

	
	turn_cards_back();
	
	SetCtrlVal (panelHandle_2, PANEL_2_SCORE, point);
	SetCtrlAttribute (panelHandle_2, PANEL_2_NAME_STRING, ATTR_DIMMED, 0);
	SetCtrlAttribute (panelHandle_2, PANEL_2_CANVAS, ATTR_DIMMED, 1);
	SetCtrlAttribute (panelHandle_2, PANEL_2_TIMER, ATTR_ENABLED, 0);
	

}

/*
void pair_random()
{
	card tempoint1;
	card tempoint2;
	int templace1, templace2, templace3;
	if(programmer_board[programmer_rand_col_1][programmer_rand_row_1] == 1) // first card check if it flip back 
	{
		while(programmer_board[programmer_rand_col_1][programmer_rand_row_1] == 1)
		{
			programmer_rand_col_1 = 1 + rand()%6; 
			programmer_rand_row_1 = 1 + rand()%6; 
			if(programmer_board[programmer_rand_col_1][programmer_rand_row_1] == 0)
			{
				point1 = MakePoint (programmer_rand_col_1, programmer_rand_row_1);
				for(int i = 0 ; i < 36 ; i++)
				{
					
					if(point1 == prog_array[i])
					{
						tempoint1 = prog_array[i];
						templace1 = i;
					}	
				}
			}
			
		}
	}			
	if(programmer_board[programmer_rand_col_2][programmer_rand_row_2] == 1) // first card check if it flip back 
	{
		while(programmer_board[programmer_rand_col_2][programmer_rand_row_2] == 1)
		{
			programmer_rand_col_2 = 1 + rand()%6; 
			programmer_rand_row_2 = 1 + rand()%6; 
			if(programmer_board[programmer_rand_col_1][programmer_rand_row_1] == 0)
			{
				point2 = MakePoint (programmer_rand_col_1, programmer_rand_row_1);
				for(int i = 0 ; i < 36 ; i++)
				{
					
					if(point2 == prog_array[i])
					{
						tempoint2 = prog_array[i];
						templace2 = i;
					}	
				}
			}
			
		}
	}
	
	if(tempoint1 != tempoint2)
	{
		prog
		
	if(tempoint1 == tempoint2)
		pair_random();
	
		
			
	
	
}
*/
void win_condition()
{
	counter_end++;

	if(counter_end==18)
	{
		MessagePopup ("Game", "Well Done!");
		SetCtrlAttribute (panelHandle_2, PANEL_2_TIMER, ATTR_ENABLED, 0);
		SetCtrlAttribute (panelHandle, PANEL_RESETBUTTON, ATTR_VISIBLE, 1);
		SetTableCellVal (panelHandle_3, PANEL_3_TABLE,  MakePoint (2,table_point), point);
		SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint (3, table_time), counter_game_time/dt);
		write_record_file();
		MessagePopup ("You have not finish here", "Are you ready for\nProgrammer Mode?");
		MessagePopup("Introduction for Programmer Mode","Now two Random cards/nwill replace there\nplace in every 8 seconds");
		game_mode == 1 ;
		NextModefunc();
	}
}

void write_record_file()
{
	FILE *fp;
	
	fp = fopen ("record_table.csv", "w");
	fprintf(fp, "%s,%d,%d\n", &players[table_place-1], point, (counter_game_time/dt));
	fclose(fp);
}

void read_record_file()
{
	FILE *fp;
	char line[100];
	char player_1[100], player_2[100], player_3[100], player_4[100], player_5[100];

	fp = fopen ("record_table.csv", "r");
	
	
	fgets (line, 99, fp);
	sscanf(line , "%[^,],%d,%d\n" , player_1 ,&points[0] ,&times[0]);
	fgets (line, 99, fp);
	sscanf(line , "%[^,],%d,%d\n" , player_2 ,&points[1] ,&times[1]);
	fgets (line, 99, fp);
	sscanf(line , "%[^,],%d,%d\n" , player_3 ,&points[2] ,&times[2]);
	fgets (line, 99, fp);
	sscanf(line , "%[^,],%d,%d\n" , player_4 ,&points[3] ,&times[3]);
	fgets (line, 99, fp);
	sscanf(line , "%[^,],%d,%d\n" , player_5 ,&points[4] ,&times[4]);
	
	
	SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint(1,1), player_1);
	SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint(1,2), player_2);
	SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint(1,3), player_3);
	SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint(1,4), player_4);
	SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint(1,5), player_5);
	
	for(int i=0 ; i<5 ; i++)
	{
		//SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint(1,(i+1)), &players[i]);
		SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint(2,(i+1)), points[i]);	
		SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint(3,(i+1)), times[i]);
	}
	
	fclose(fp);	
}


