#include "bass.h" 
#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "MemoryGame.h"


typedef struct
{
	int col;
	int row;
}cards;

cards card_place_a;
cards card_place_a_2;
cards card_place_b;
cards card_place_b_2;
cards card_place_c;
cards card_place_c_2;
cards card_place_d;
cards card_place_d_2;
cards card_place_e;
cards card_place_e_2;
cards card_place_f;
cards card_place_f_2;
cards card_place_g;
cards card_place_g_2;
cards card_place_h;
cards card_place_h_2;
cards card_place_i;
cards card_place_i_2;
cards card_place_j;
cards card_place_j_2;
cards card_place_k;
cards card_place_k_2;
cards card_place_l;
cards card_place_l_2;
cards card_place_m;
cards card_place_m_2;
cards card_place_n;
cards card_place_n_2;
cards card_place_o;
cards card_place_o_2;
cards card_place_p;
cards card_place_p_2;
cards card_place_q;
cards card_place_q_2;
cards card_place_r;
cards card_place_r_2;

cards card_temp_1;
cards card_temp_2;

HSTREAM card_flip_SND;
HSTREAM win_SND;
HSTREAM start_SND;

static int panelHandle, panelHandle_2, panelHandle_3, panelHandle_4;

//Random cards on board
int random_num, rand_col, rand_row;
int a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0, i=0, j=0, k=0, l=0, m=0, n=0, o=0, p=0, q=0, r = 0;
int game_col=100, game_row=100, game_col_1=100, game_row_1=100; //defined to 100 because {0,0} is acctualy cell: col 0, row 0
int board[7][7]={{0}};

//General counters and flags
int counter=0, counter_3=0, counter_end=0;
int table_point=1, table_time=1, table_place=1;
int load_row=0;
int flag=0, flag_2=0, flag_pause=0;

//Points
int point=3;

//time calculate variables
int counter_2=0, dt=50, temp_time=0;

//Bitmaps variables
int card_a, card_b, card_c, card_d, card_e, card_f, card_g, card_h, card_i, card_j, card_k, card_l, card_m, card_n, card_o, card_p, card_q, card_r;
int cardsback;

//spliting the canvas to squres
int rows=6, cols=6;
int box_width=90, box_height=90;

//Strings and other arrays
char player_name[100], record_table[300];
char players[5000];
int points[500]={{0}}, times[500]={{0}}; 

//Functions
void initialize();
void terminate();
void draw_back_cards();
void game_time();
void mouse_click();
void random();
void draw_card_on_place();
void check_same_card();
void end_condition();
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
	start_SND = BASS_StreamCreateFile(FALSE,"start.mp3",0,0,0);
}

void ReleaseMP3s(void)
{
	 BASS_StreamFree(card_flip_SND);
	 BASS_StreamFree(win_SND);
	 BASS_StreamFree(start_SND);
}

void initialize()
{
	read_record_file();
	
	InitMP3s();
	BASS_ChannelPlay(start_SND,TRUE);
	
	GetBitmapFromFile ("pictures//cardsback.png", &cardsback);
	GetBitmapFromFile ("pictures//a.png", &card_a);
	GetBitmapFromFile ("pictures//b.png", &card_b);
	GetBitmapFromFile ("pictures//c.png", &card_c);
	GetBitmapFromFile ("pictures//d.png", &card_d);
	GetBitmapFromFile ("pictures//e.png", &card_e);
	GetBitmapFromFile ("pictures//f.png", &card_f);
	GetBitmapFromFile ("pictures//g.png", &card_g);
	GetBitmapFromFile ("pictures//h.png", &card_h);
	GetBitmapFromFile ("pictures//i.png", &card_i);
	GetBitmapFromFile ("pictures//j.png", &card_j);
	GetBitmapFromFile ("pictures//k.png", &card_k);
	GetBitmapFromFile ("pictures//l.png", &card_l);
	GetBitmapFromFile ("pictures//m.png", &card_m);
	GetBitmapFromFile ("pictures//n.png", &card_n);
	GetBitmapFromFile ("pictures//o.png", &card_o);
	GetBitmapFromFile ("pictures//p.png", &card_p);
	GetBitmapFromFile ("pictures//q.png", &card_q);
	GetBitmapFromFile ("pictures//r.png", &card_r);

	draw_back_cards();
}

void terminate()
{
	ReleaseMP3s();
	
	DiscardBitmap(cardsback);
	DiscardBitmap(card_a);
	DiscardBitmap(card_b);
	DiscardBitmap(card_c);
	DiscardBitmap(card_d);
	DiscardBitmap(card_e);
	DiscardBitmap(card_f);
	DiscardBitmap(card_g);
	DiscardBitmap(card_h);
	DiscardBitmap(card_i);
	DiscardBitmap(card_j);
	DiscardBitmap(card_k);
	DiscardBitmap(card_l);
	DiscardBitmap(card_m);
	DiscardBitmap(card_n);
	DiscardBitmap(card_o);
	DiscardBitmap(card_p);
	DiscardBitmap(card_q);
	DiscardBitmap(card_r);
}

int CVICALLBACK PanelFunc (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

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

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (panelHandle_2);
			BASS_ChannelPlay(start_SND,TRUE);
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

void draw_back_cards()
{
	CanvasStartBatchDraw (panelHandle_2, PANEL_2_CANVAS);
	
	for(int i=0 ; i<6 ; i++)
		for(int j=0 ; j<6 ; j++)
		{
			CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, cardsback, VAL_ENTIRE_OBJECT, MakeRect(90*i,90*j,90,90));
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
			
			BASS_ChannelStop(start_SND);
			
			DisplayPanel (panelHandle_2);
			
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
			counter_2=0;
			counter_3=0;
			counter_end=0;
			flag=0;
			flag_2=0;
			point=3;
			
			draw_back_cards();
			
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

void game_time()
{
	SetCtrlVal (panelHandle_2, PANEL_2_TIME, counter_2/dt);
	
	counter_2++;
}

void CVICALLBACK MenuHelpFunc (int menuBar, int menuItem, void *callbackData,
							   int panel)
{
	switch(panel)
	{
		case EVENT_COMMIT:
			
			BASS_ChannelStop(start_SND);
			OpenDocumentInDefaultViewer ("Help.pdf", VAL_NO_ZOOM);
			
			break;
	}
}

void CVICALLBACK MenuDemoFunc (int menuBar, int menuItem, void *callbackData,
							   int panel)
{
	 BASS_ChannelStop(start_SND);
	 OpenDocumentInDefaultViewer ("Video.mp4", VAL_NO_ZOOM);
}

int CVICALLBACK TimerFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			game_time();
			
			if(flag == 0) //only if there are cards without place
				random();

			break;
	}
	return 0;
}

void mouse_click()
{
	 static int x=0, y=0;
	
	 counter_3++; // count number of moves
			
			if(counter_3 == 10) // every 5 moves and if the player didnt founded match, then minus 1 point
			{
				if(point>0)
				{
					point--;
					SetCtrlVal (panelHandle_2, PANEL_2_SCORE, point);
				}
				counter_3=0;
			}
			
			if(counter < 2) //press on board 1 or 2 times only
			{
				GetRelativeMouseState (panelHandle_2, PANEL_2_CANVAS, &x, &y, 0, 0, 0);
				game_col = x/box_width;
				game_row = y/box_height;
				
				if(board[game_col][game_row] < 2) //the player is not alowed to flip open card that has a couple allready
				{
					if(game_col != game_col_1 || game_row != game_row_1) //prevent the player to press the same card
							{
								BASS_ChannelPlay(card_flip_SND,TRUE);
							
								counter++; //count number of clicks	
					
								game_col_1 = game_col;
								game_row_1 = game_row;
					
								if(counter==1) //first card chose
								{
									if(flag_2==0) //if the two cards that are open, are not the same, so close them
									{
										CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, cardsback, VAL_ENTIRE_OBJECT,
														  MakeRect(90*(card_temp_1.row),90*(card_temp_1.col),90,90));
										CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, cardsback, VAL_ENTIRE_OBJECT,
														  MakeRect(90*(card_temp_2.row),90*(card_temp_2.col),90,90));
									}
						
									card_temp_1.row = game_row_1;
								    card_temp_1.col = game_col_1;
									draw_card_on_place();
								}
					
								if(counter==2) //second card chose
								{
									card_temp_2.row = game_row_1;
								    card_temp_2.col = game_col_1;
									draw_card_on_place();
									
									check_same_card();
						
									counter=0;
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

void draw_card_on_place()
{
	
	if(card_place_a.col == game_col_1  && card_place_a.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_a, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_a.row), 90*(card_place_a.col),90,90));		
	
	if(card_place_b.col == game_col_1  && card_place_b.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_b, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_b.row), 90*(card_place_b.col),90,90));
	
	if(card_place_c.col == game_col_1  && card_place_c.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_c, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_c.row), 90*(card_place_c.col),90,90));
	
	if(card_place_d.col == game_col_1  && card_place_d.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_d, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_d.row), 90*(card_place_d.col),90,90));
	
	if(card_place_e.col == game_col_1  && card_place_e.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_e, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_e.row), 90*(card_place_e.col),90,90));
	
	if(card_place_f.col == game_col_1  && card_place_f.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_f, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_f.row), 90*(card_place_f.col),90,90));
	
	if(card_place_g.col == game_col_1  && card_place_g.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_g, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_g.row), 90*(card_place_g.col),90,90));
	
	if(card_place_h.col == game_col_1  && card_place_h.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_h, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_h.row), 90*(card_place_h.col),90,90));
	
	if(card_place_i.col == game_col_1  && card_place_i.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_i, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_i.row), 90*(card_place_i.col),90,90));
	
	if(card_place_j.col == game_col_1  && card_place_j.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_j, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_j.row), 90*(card_place_j.col),90,90));
	
	if(card_place_k.col == game_col_1  && card_place_k.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_k, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_k.row), 90*(card_place_k.col),90,90));
	
	if(card_place_l.col == game_col_1  && card_place_l.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_l, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_l.row), 90*(card_place_l.col),90,90));
	
	if(card_place_m.col == game_col_1  && card_place_m.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_m, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_m.row), 90*(card_place_m.col),90,90));
	
	if(card_place_n.col == game_col_1  && card_place_n.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_n, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_n.row), 90*(card_place_n.col),90,90));
	
	if(card_place_o.col == game_col_1  && card_place_o.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_o, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_o.row), 90*(card_place_o.col),90,90));
	
	if(card_place_p.col == game_col_1  && card_place_p.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_p, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_p.row), 90*(card_place_p.col),90,90));
	
	if(card_place_q.col == game_col_1  && card_place_q.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_q, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_q.row), 90*(card_place_q.col),90,90));
	
	if(card_place_r.col == game_col_1  && card_place_r.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_r, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_r.row), 90*(card_place_r.col),90,90));
	
	
	if(card_place_a_2.col == game_col_1  && card_place_a_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_a, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_a_2.row), 90*(card_place_a_2.col),90,90));		
	
	if(card_place_b_2.col == game_col_1  && card_place_b_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_b, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_b_2.row), 90*(card_place_b_2.col),90,90));
	
	if(card_place_c_2.col == game_col_1  && card_place_c_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_c, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_c_2.row), 90*(card_place_c_2.col),90,90));
	
	if(card_place_d_2.col == game_col_1  && card_place_d_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_d, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_d_2.row), 90*(card_place_d_2.col),90,90));
	
	if(card_place_e_2.col == game_col_1  && card_place_e_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_e, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_e_2.row), 90*(card_place_e_2.col),90,90));
	
	if(card_place_f_2.col == game_col_1  && card_place_f_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_f, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_f_2.row), 90*(card_place_f_2.col),90,90));
	
	if(card_place_g_2.col == game_col_1  && card_place_g_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_g, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_g_2.row), 90*(card_place_g_2.col),90,90));
	
	if(card_place_h_2.col == game_col_1  && card_place_h_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_h, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_h_2.row), 90*(card_place_h_2.col),90,90));
	
	if(card_place_i_2.col == game_col_1  && card_place_i_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_i, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_i_2.row), 90*(card_place_i_2.col),90,90));
	
	if(card_place_j_2.col == game_col_1  && card_place_j_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_j, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_j_2.row), 90*(card_place_j_2.col),90,90));
	
	if(card_place_k_2.col == game_col_1  && card_place_k_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_k, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_k_2.row), 90*(card_place_k_2.col),90,90));
	
	if(card_place_l_2.col == game_col_1  && card_place_l_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_l, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_l_2.row), 90*(card_place_l_2.col),90,90));
	
	if(card_place_m_2.col == game_col_1  && card_place_m_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_m, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_m_2.row), 90*(card_place_m_2.col),90,90));
	
	if(card_place_n_2.col == game_col_1  && card_place_n_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_n, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_n_2.row), 90*(card_place_n_2.col),90,90));
	
	if(card_place_o_2.col == game_col_1  && card_place_o_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_o, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_o_2.row), 90*(card_place_o_2.col),90,90));
	
	if(card_place_p_2.col == game_col_1  && card_place_p_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_p, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_p_2.row), 90*(card_place_p_2.col),90,90));
	
	if(card_place_q_2.col == game_col_1  && card_place_q_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_q, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_q_2.row), 90*(card_place_q_2.col),90,90));
	
	if(card_place_r_2.col == game_col_1  && card_place_r_2.row == game_row_1)
		CanvasDrawBitmap (panelHandle_2, PANEL_2_CANVAS, card_r, VAL_ENTIRE_OBJECT, MakeRect(90*(card_place_r_2.row), 90*(card_place_r_2.col),90,90));
}

void random()
{
	random_num = 1 + rand()%18; // choose card

	if(flag == 0) // prevent the Timer from another random cards round
	{
		if (random_num == 1 && a < 2) 
		{
            if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random place is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				
				if(a==0) //first time to chose card a
				{
					card_place_a.col = rand_col-1;
					card_place_a.row = rand_row-1;
				}
				
				if(a==1) //second time to chose card a
				{
					card_place_a_2.col = rand_col-1;
					card_place_a_2.row = rand_row-1;
				}
				
				a++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 2 && b < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(b==0)
				{
					card_place_b.col = rand_col-1;
					card_place_b.row = rand_row-1;
				}
				
				if(b==1)
				{
					card_place_b_2.col = rand_col-1;
					card_place_b_2.row = rand_row-1;	
				}
				b++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 3 && c < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(c==0)
				{
					card_place_c.col = rand_col-1;
					card_place_c.row = rand_row-1;
				}
				
				if(c==1)
				{
					card_place_c_2.col = rand_col-1;
					card_place_c_2.row = rand_row-1;	
				}
				c++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 4 && d < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(d==0)
				{
					card_place_d.col = rand_col-1;
					card_place_d.row = rand_row-1;
				}
				
				if(d==1)
				{
					card_place_d_2.col = rand_col-1;
					card_place_d_2.row = rand_row-1;	
				}
				d++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 5 && e < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(e==0)
				{
					card_place_e.col = rand_col-1;
					card_place_e.row = rand_row-1;
				}
				
				if(e==1)
				{
					card_place_e_2.col = rand_col-1;
					card_place_e_2.row = rand_row-1;	
				}
				e++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 6 && f < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(f==0)
				{
					card_place_f.col = rand_col-1;
					card_place_f.row = rand_row-1;
				}
				
				if(f==1)
				{
					card_place_f_2.col = rand_col-1;
					card_place_f_2.row = rand_row-1;	
				}
				f++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 7 && g < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(g==0)
				{
					card_place_g.col = rand_col-1;
					card_place_g.row = rand_row-1;
				}
				
				if(g==1)
				{
					card_place_g_2.col = rand_col-1;
					card_place_g_2.row = rand_row-1;	
				}
				g++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 8 && h < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(h==0)
				{
					card_place_h.col = rand_col-1;
					card_place_h.row = rand_row-1;
				}
				
				if(h==1)
				{
					card_place_h_2.col = rand_col-1;
					card_place_h_2.row = rand_row-1;	
				}
				h++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 9 && i < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(i==0)
				{
					card_place_i.col = rand_col-1;
					card_place_i.row = rand_row-1;
				}
				
				if(i==1)
				{
					card_place_i_2.col = rand_col-1;
					card_place_i_2.row = rand_row-1;	
				}
				i++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 10 && j < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(j==0)
				{
					card_place_j.col = rand_col-1;
					card_place_j.row = rand_row-1;
				}
				
				if(j==1)
				{
					card_place_j_2.col = rand_col-1;
					card_place_j_2.row = rand_row-1;	
				}
				j++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 11 && k < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(k==0)
				{
					card_place_k.col = rand_col-1;
					card_place_k.row = rand_row-1;
				}
				
				if(k==1)
				{
					card_place_k_2.col = rand_col-1;
					card_place_k_2.row = rand_row-1;	
				}
				k++; // tells the number of cards with the same name is on the board.
			}
		}

		if (random_num == 12 && l < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(l==0)
				{
					card_place_l.col = rand_col-1;
					card_place_l.row = rand_row-1;
				}
				
				if(l==1)
				{
					card_place_l_2.col = rand_col-1;
					card_place_l_2.row = rand_row-1;
				}
				l++; // tells the number of cards with the same name is on the board.
			}
		}
		
		if (random_num == 13 && m < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(m==0)
				{
					card_place_m.col = rand_col-1;
					card_place_m.row = rand_row-1;
				}
				
				if(m==1)
				{
					card_place_m_2.col = rand_col-1;
					card_place_m_2.row = rand_row-1;	
				}
				m++; // tells the number of cards with the same name is on the board.
			}
		}
		
		if (random_num == 14 && n < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(n==0)
				{
					card_place_n.col = rand_col-1;
					card_place_n.row = rand_row-1;
				}
				
				if(n==1)
				{
					card_place_n_2.col = rand_col-1;
					card_place_n_2.row = rand_row-1;	
				}
				n++; // tells the number of cards with the same name is on the board.
			}
		}
		
		if (random_num == 15 && o < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(o==0)
				{
					card_place_o.col = rand_col-1;
					card_place_o.row = rand_row-1;
				}
				
				if(o==1)
				{
					card_place_o_2.col = rand_col-1;
					card_place_o_2.row = rand_row-1;	
				}
				o++; // tells the number of cards with the same name is on the board.
			}
		}
		
		if (random_num == 16 && p < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(p==0)
				{
					card_place_p.col = rand_col-1;
					card_place_p.row = rand_row-1;
				}
				
				if(p==1)
				{
					card_place_p_2.col = rand_col-1;
					card_place_p_2.row = rand_row-1;	
				}
				p++; // tells the number of cards with the same name is on the board.
			}
		}
		
		if (random_num == 17 && q < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(q==0)
				{
					card_place_q.col = rand_col-1;
					card_place_q.row = rand_row-1;
				}
				
				if(q==1)
				{
					card_place_q_2.col = rand_col-1;
					card_place_q_2.row = rand_row-1;	
				}
				q++; // tells the number of cards with the same name is on the board.
			}
		}
		
		if (random_num == 18&& r < 2) 
		{
			if(point<18)
			{
				rand_col = 1 + rand()%6; // choose random place on col
				rand_row = 1 + rand()%6; // choose random place on row
			}
			if (board[rand_col][rand_row] == 0) // if the random palce is with card or not
			{
				board[rand_col][rand_row] = 1; // set board in rand_row, rand_col to full -> 1.
				if(r==0)
				{
					card_place_r.col = rand_col-1;
					card_place_r.row = rand_row-1;
				}
				
				if(r==1)
				{
					card_place_r_2.col = rand_col-1;
					card_place_r_2.row = rand_row-1;	
				}
				r++; // tells the number of cards with the same name is on the board.
			}
		}
	}
	
	if(a==2 && b==2 && c==2 && d==2 && e==2 && f==2 && g==2 && h==2 && i==2 && j==2 && k==2 && l==2 && m==2 && n==2 && o==2 && p==2 && q==2 && r==2)
		flag=1;
	
}

void check_same_card()
{
	flag_2=0;									 
	
	if((card_temp_1.row == card_place_a.row) && (card_temp_1.col == card_place_a.col))
	{
		if((card_temp_2.row == card_place_a_2.row) && (card_temp_2.col == card_place_a_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_a_2.row) && (card_temp_1.col == card_place_a_2.col))
	{
		if((card_temp_2.row == card_place_a.row) && (card_temp_2.col == card_place_a.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_b.row) && (card_temp_1.col == card_place_b.col))
	{
		if((card_temp_2.row == card_place_b_2.row) && (card_temp_2.col == card_place_b_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_b_2.row) && (card_temp_1.col == card_place_b_2.col))
	{
		if((card_temp_2.row == card_place_b.row) && (card_temp_2.col == card_place_b.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_c.row) && (card_temp_1.col == card_place_c.col))
	{
		if((card_temp_2.row == card_place_c_2.row) && (card_temp_2.col == card_place_c_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_c_2.row) && (card_temp_1.col == card_place_c_2.col))
	{
		if((card_temp_2.row == card_place_c.row) && (card_temp_2.col == card_place_c.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_d.row) && (card_temp_1.col == card_place_d.col))
	{
		if((card_temp_2.row == card_place_d_2.row) && (card_temp_2.col == card_place_d_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_d_2.row) && (card_temp_1.col == card_place_d_2.col))
	{
		if((card_temp_2.row == card_place_d.row) && (card_temp_2.col == card_place_d.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_e.row) && (card_temp_1.col == card_place_e.col))
	{
		if((card_temp_2.row == card_place_e_2.row) && (card_temp_2.col == card_place_e_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_e_2.row) && (card_temp_1.col == card_place_e_2.col))
	{
		if((card_temp_2.row == card_place_e.row) && (card_temp_2.col == card_place_e.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_f.row) && (card_temp_1.col == card_place_f.col))
	{
		if((card_temp_2.row == card_place_f_2.row) && (card_temp_2.col == card_place_f_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_f_2.row) && (card_temp_1.col == card_place_f_2.col))
	{
		if((card_temp_2.row == card_place_f.row) && (card_temp_2.col == card_place_f.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_g.row) && (card_temp_1.col == card_place_g.col))
	{
		if((card_temp_2.row == card_place_g_2.row) && (card_temp_2.col == card_place_g_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_g_2.row) && (card_temp_1.col == card_place_g_2.col))
	{
		if((card_temp_2.row == card_place_g.row) && (card_temp_2.col == card_place_g.col))
		{
			flag_2=1;
		}
	}
	
	
	if((card_temp_1.row == card_place_h.row) && (card_temp_1.col == card_place_h.col))
	{
		if((card_temp_2.row == card_place_h_2.row) && (card_temp_2.col == card_place_h_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_h_2.row) && (card_temp_1.col == card_place_h_2.col))
	{
		if((card_temp_2.row == card_place_h.row) && (card_temp_2.col == card_place_h.col))
		{
			flag_2=1;
		}
	}
	
	
	
	if((card_temp_1.row == card_place_i.row) && (card_temp_1.col == card_place_i.col))
	{
		if((card_temp_2.row == card_place_i_2.row) && (card_temp_2.col == card_place_i_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_i_2.row) && (card_temp_1.col == card_place_i_2.col))
	{
		if((card_temp_2.row == card_place_i.row) && (card_temp_2.col == card_place_i.col))
		{
			flag_2=1;
		}
	}
	
	
	if((card_temp_1.row == card_place_j.row) && (card_temp_1.col == card_place_j.col))
	{
		if((card_temp_2.row == card_place_j_2.row) && (card_temp_2.col == card_place_j_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_j_2.row) && (card_temp_1.col == card_place_j_2.col))
	{
		if((card_temp_2.row == card_place_j.row) && (card_temp_2.col == card_place_j.col))
		{
			flag_2=1;
		}
	}
	
	
	if((card_temp_1.row == card_place_k.row) && (card_temp_1.col == card_place_k.col))
	{
		if((card_temp_2.row == card_place_k_2.row) && (card_temp_2.col == card_place_k_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_k_2.row) && (card_temp_1.col == card_place_k_2.col))
	{
		if((card_temp_2.row == card_place_k.row) && (card_temp_2.col == card_place_k.col))
		{
			flag_2=1;
		}
	}
	
	
	if((card_temp_1.row == card_place_l.row) && (card_temp_1.col == card_place_l.col))
	{
		if((card_temp_2.row == card_place_l_2.row) && (card_temp_2.col == card_place_l_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_l_2.row) && (card_temp_1.col == card_place_l_2.col))
	{
		if((card_temp_2.row == card_place_l.row) && (card_temp_2.col == card_place_l.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_m.row) && (card_temp_1.col == card_place_m.col))
	{
		if((card_temp_2.row == card_place_m_2.row) && (card_temp_2.col == card_place_m_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_m_2.row) && (card_temp_1.col == card_place_m_2.col))
	{
		if((card_temp_2.row == card_place_m.row) && (card_temp_2.col == card_place_m.col))
		{
			flag_2=1;
		}
	}
	if((card_temp_1.row == card_place_n.row) && (card_temp_1.col == card_place_n.col))
	{
		if((card_temp_2.row == card_place_n_2.row) && (card_temp_2.col == card_place_n_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_n_2.row) && (card_temp_1.col == card_place_n_2.col))
	{
		if((card_temp_2.row == card_place_n.row) && (card_temp_2.col == card_place_n.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_o.row) && (card_temp_1.col == card_place_o.col))
	{
		if((card_temp_2.row == card_place_o_2.row) && (card_temp_2.col == card_place_o_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_o_2.row) && (card_temp_1.col == card_place_o_2.col))
	{
		if((card_temp_2.row == card_place_o.row) && (card_temp_2.col == card_place_o.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_p.row) && (card_temp_1.col == card_place_p.col))
	{
		if((card_temp_2.row == card_place_p_2.row) && (card_temp_2.col == card_place_p_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_p_2.row) && (card_temp_1.col == card_place_p_2.col))
	{
		if((card_temp_2.row == card_place_p.row) && (card_temp_2.col == card_place_p.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_q.row) && (card_temp_1.col == card_place_q.col))
	{
		if((card_temp_2.row == card_place_q_2.row) && (card_temp_2.col == card_place_q_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_q_2.row) && (card_temp_1.col == card_place_q_2.col))
	{
		if((card_temp_2.row == card_place_q.row) && (card_temp_2.col == card_place_q.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_r.row) && (card_temp_1.col == card_place_r.col))
	{
		if((card_temp_2.row == card_place_r_2.row) && (card_temp_2.col == card_place_r_2.col))
		{
			flag_2=1;
		}
	}
	
	if((card_temp_1.row == card_place_r_2.row) && (card_temp_1.col == card_place_r_2.col))
	{
		if((card_temp_2.row == card_place_r.row) && (card_temp_2.col == card_place_r.col))
		{
			flag_2=1;
		}
	}
	
	
	
	if(flag_2==1)
	{
		BASS_ChannelPlay(win_SND,TRUE);
		
		point++;
		
		SetCtrlVal (panelHandle_2, PANEL_2_SCORE, point);
		
		board[card_temp_1.col][card_temp_1.row]=2;
		board[card_temp_2.col][card_temp_2.row]=2;
		
		end_condition();
		
		counter_3=0;
	}
}

void end_condition()
{
	counter_end++;

	if(counter_end==18)
	{
		MessagePopup ("Game", "Well Done!");
		SetCtrlAttribute (panelHandle_2, PANEL_2_TIMER, ATTR_ENABLED, 0);
		SetCtrlAttribute (panelHandle, PANEL_RESETBUTTON, ATTR_VISIBLE, 1);
		SetTableCellVal (panelHandle_3, PANEL_3_TABLE,  MakePoint (2,table_point), point);
		SetTableCellVal (panelHandle_3, PANEL_3_TABLE, MakePoint (3, table_time), counter_2/dt);
		write_record_file();
	}
}

void write_record_file()
{
	FILE *fp;
	
	fp = fopen ("record_table.csv", "w");
	fprintf(fp, "%s,%d,%d\n", &players[table_place-1], point, (counter_2/dt));
	fclose(fp);
}

void read_record_file()
{
	FILE *fp;
	char line[100];
	char player_1[100], player_2[100], player_3[100], player_4[100], player_5[100];
	int load_row=0;

	fp = fopen ("record_table.csv", "r");
	
	/* //didnt work with the string, that the reason there are 5 fgets...
	while(fgets (line, 99, fp) != 0)
	{
		sscanf(line , "%[^,],%d,%d\n" , &players[load_row] ,&points[load_row] ,&times[load_row]);
		load_row++;
	}
	*/
	
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
