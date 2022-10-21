/*PING-PONG 
 * This is a 2 player game
 * Each player gets 2 buttons to control pad upwards or downwards
 * 16x2 Alphanumeric LCD is taken as display unit
 * Developed by : Soham Patel
 * Date: Feb 2019 
 * Contact : patelsoham002@gmail.com
 */
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

#define P1U 9
#define P1D 8
#define P2U 7
#define P2D 6
#define PAD_START 9
#define COL_START1 13
#define COL_START0 2 
#define UPPER 0
#define LOWER 8
#define SENSITIVITY_PAD 500           //decrease value to increase sensitivity
#define BALL_SPEED 500                //decrease value to increase ball speed
#define RANDOM_PARAMETER millis()      //for simulation only, less preferable
//#define RANDOM_PARAMETER analogRead(0) //for real time hardware, more preferable


//player 1 pad positions from up to down
byte pad0_pos[10][16]={
  {
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00001,
    B00001,
    B00001,
    B00001,
    B00000,

    B00001,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00001,
    B00001,
    B00001,
    B00000,

    B00001,
    B00001,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00001,
    B00001,
    B00000,

    B00001,
    B00001,
    B00001,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00001,
    B00000,

    B00001,
    B00001,
    B00001,
    B00001,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00000,
  }
};

//player 2 pad positions from up to down
byte pad1_pos[10][16]={
  {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,

    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B10000,
    B10000,
    B10000,
    B00000,

    B10000,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B10000,
    B10000,
    B00000,

    B10000,
    B10000,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B10000,
    B00000,

    B10000,
    B10000,
    B10000,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,
  }
};

//ball postions 
byte ball_pos[12][16]={
  {
    B11100,
    B11100,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B11100,
    B11100,
    B11100,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B11100,
    B11100,
    B11100,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00111,
    B00111,
    B00111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00111,
    B00111,
    B00111,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00111,
    B00111,
    B00111,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B11100,
    B11100,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B11100,
    B11100,
    B11100,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B11100,
    B11100,
    B11100,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00111,
    B00111,
    B00111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00111,
    B00111,
    B00111,
    B00000,
    B00000,
    B00000,
  },
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,

    B00000,
    B00000,
    B00000,
    B00000,
    B00111,
    B00111,
    B00111,
    B00000,
  }
};

//Scores from 0 to 3 
byte score[4][8]={
  {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
  },
  {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B00000,
  },
  {
    B10100,
    B10100,
    B10100,
    B10100,
    B10100,
    B10100,
    B10100,
    B00000,
  },
  {
    B10101,
    B10101,
    B10101,
    B10101,
    B10101,
    B10101,
    B10101,
    B00000,
  }
};

void setup() {
  // initialzie input pins and activate built-in pull-up resistor of each input
  pinMode(P1U,INPUT_PULLUP); //player 1 up button
  pinMode(P2U,INPUT_PULLUP); //player 2 down button
  pinMode(P1D,INPUT_PULLUP); //player 1 down button
  pinMode(P2D,INPUT_PULLUP); //player 2 down button
  
  lcd.begin(16,2); //16x2 lcd initialize
}

unsigned char player,score0,score1,ball_loc,pad1,pad0,ball_col,sig,prev=20,hit;
unsigned int sens_pad0,sens_pad1,ball_cnt;

void loop() 
{
  initial();
  randomSeed(RANDOM_PARAMETER);
  player=random(2);
  game_start();
  play_start();
  while(1);
}

//inital setup for new game
void initial()
{
  score0=0;
  score1=0;
  pad1=PAD_START;
  pad0=PAD_START;
  prev=20;
  hit=0;
  sig=0;
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("PING-PONG");
  lcd.setCursor(1,1);
  lcd.print("Start new game?");
  while(digitalRead(P1U) && digitalRead(P2U) && digitalRead(P1D) && digitalRead(P2D));
  while(!(digitalRead(P1U) && digitalRead(P2U) && digitalRead(P1D) && digitalRead(P2D)));
  lcd.clear();
}

//initial setup after each point scored
void game_start()
{
  game_start_printer();
  lcd.setCursor(0,0);
  lcd.print(1);
  lcd.setCursor(15,0);
  lcd.print(2);
  lcd.setCursor(5,1);
  lcd.print("READY?");
  while(digitalRead(P1U) && digitalRead(P2U) && digitalRead(P1D) && digitalRead(P2D));
  lcd.setCursor(5,1);
  lcd.print("      ");
}

//used to update stats and random ball location after each point
void game_start_printer()
{
  if(sig==1)
  ball_clear();
  sig=0;
  score_print();
  pad1_print();
  pad0_print();
  randomSeed(RANDOM_PARAMETER);
  if(player)
  {
    ball_loc=random(3,6);
    ball_col=COL_START1;
    ball();
  }
  else
  {
    ball_loc=random(0,3);
    ball_col=COL_START0;
    ball();
  }
}

//used to print ball
void ball()
{
  lcd.createChar(3,&ball_pos[ball_loc][UPPER]);
  lcd.createChar(4,&ball_pos[ball_loc][LOWER]);
  lcd.setCursor(ball_col,0);
  lcd.write(byte(3));
  lcd.setCursor(ball_col,1);
  lcd.write(byte(4));
}

//used to erase last location of ball
void ball_clear()
{
  lcd.setCursor(ball_col,0);
  lcd.print(" ");
  lcd.setCursor(ball_col,1);
  lcd.print(" ");
}

//used to print pad of player 2
void pad1_print()
{
  lcd.createChar(2,&pad1_pos[pad1][UPPER]);
  lcd.createChar(7,&pad1_pos[pad1][LOWER]);
  lcd.setCursor(14,0);
  lcd.write(byte(2));
  lcd.setCursor(14,1);
  lcd.write(byte(7));
}

//used to print pad of player 1
void pad0_print()
{
  lcd.createChar(0,&pad0_pos[pad0][UPPER]);
  lcd.createChar(1,&pad0_pos[pad0][LOWER]);
  lcd.setCursor(1,0);
  lcd.write(byte(0));
  lcd.setCursor(1,1);
  lcd.write(byte(1));
}

//used to print scores and decide if there is a winner
void score_print()
{
  if(score0==4)
  win(0);
  else if(score1==4)
  win(1);
  else{
  lcd.createChar(5,&score[score0][UPPER]);
  lcd.createChar(6,&score[score1][UPPER]);
  lcd.setCursor(0,1);
  lcd.write(byte(5));
  lcd.setCursor(15,1);
  lcd.write(byte(6));
}
}

//whole play is managed here
void play_start()
{
  l1:while(!target_in_range())
  {
    check_input();
  }
  if(player)
  player=0;
  else
  player=1;
  while(1)
  {
    ball_play();
    if((hit==0) && (sig==1) && ((ball_col==2 && (ball_loc<=2 || ball_loc==6 || ball_loc==7 || ball_loc==8)) || (ball_col==13 && (ball_loc>=9 || ball_loc==3 || ball_loc==4 || ball_loc==5))) )
    {
      if(target_in_range())
      {
        if(player)
        player=0;
        else
        player=1;
        hit=1;
      }
      else
      {
        if(player)
        score0++;
        else
        score1++;
        lcd.setCursor(5,1);
        lcd.print("MISSED!");
        delay(1000);
        lcd.setCursor(5,1);
        lcd.print("       ");
        score_print();
        game_start();
        goto l1;
      }
    }
    check_input();
  }
}

//to check and respond to key presses by both players 
void check_input()
{
    if(!digitalRead(P1U))
    pad0_run(1);
    if(!digitalRead(P1D))
    pad0_run(0);
    if(!digitalRead(P2U))
    pad1_run(1);
    if(!digitalRead(P2D))
    pad1_run(0);
}

//to check whether ball is being hit by pad or not
unsigned char target_in_range()
{
  if(player)
  {
    switch(ball_loc){
      case 3:
      if(pad1==0 || pad1==1 || pad1==2)
      return true;
      else 
      return false;
      break;
      case 4:
      if(pad1==0 || pad1==1 || pad1==2 || pad1==3)
      return true;
      else
      return false;
      break;
      case 5:
      if(pad1==2 || pad1==3 || pad1==4 || pad1==1)
      return true;
      else
      return false;
      break;
      case 9:
      if(pad1==5 || pad1==6 || pad1==7 || pad1==8 || pad1==4)
      return true;
      else
      return false;
      break;
      case 10:
      if(pad1==7 || pad1==8 || pad1==9 || pad1==6)
      return true;
      else
      return false;
      break;
      case 11:
      if(pad1==9 || pad1==8 || pad1==7)
      return true;
      else
      return false;
      break;
      default:
      return false;
    }
  }
    else
  {
      switch(ball_loc){
      case 0:
      if(pad0==0 || pad0==1 || pad0==2)
      return true;
      else
      return false;
      break;
      case 1:
      if(pad0==0 || pad0==1 || pad0==2 || pad0==3)
      return true;
      else
      return false;
      break;
      case 2:
      if(pad0==2 || pad0==3 || pad0==4 || pad0==1)
      return true;
      else
      return false;
      break;
      case 6:
      if(pad0==5 || pad0==6 || pad0==7 || pad0==8 || pad0==4)
      return true;
      else
      return false;
      break;
      case 7:
      if(pad0==7 || pad0==8 || pad0==9 || pad0==6)
      return true;
      else
      return false;
      break;
      case 8:
      if(pad0==9 || pad0==8 || pad0==7)
      return true;
      else
      return false;
      break;
      default:
      return false;
    }
  }
}

//whole ball play is controlled here
void ball_play()
{
  if(ball_cnt==BALL_SPEED)
  {
    ball_cnt=0;
    sig=1;
    hit=0;
    switch(ball_loc){
      case 0:
      if(player==0)
      {
        ball_clear();
        ball_col--; 
      }
      prev=ball_loc;
      ball_loc=4;
      ball();
      break;
      case 3:
      if(player)
      {
        ball_clear();
        ball_col++; 
      }
      prev=ball_loc;
      ball_loc=1;
      ball();
      break;
      case 1:
      if(player==0)
      {
        ball_clear();
        ball_col--; 
      }
      if(prev==20)
      {
        randomSeed(RANDOM_PARAMETER);
        prev=random(3,5);
      }
      if(prev==3)
      ball_loc=5;
      else
      ball_loc=3;
      prev=1;
      ball();
      break;
      case 4:
      if(player)
      {
        ball_clear();
        ball_col++; 
      }
      if(prev==20)
      {
        randomSeed(RANDOM_PARAMETER);
        prev=random(2);
      }
      if(prev==0)
      ball_loc=2;
      else
      ball_loc=0;
      prev=4;
      ball();
      break;
      case 2:
      if(player==0)
      {
        ball_clear();
        ball_col--; 
      }
      if(prev==20)
      {
        randomSeed(RANDOM_PARAMETER);
        prev=random(4,6);
      }
      if(prev==4)
      ball_loc=9;
      else
      ball_loc=4;
      prev=2;
      ball();
      break;
      case 5:
      if(player)
      {
        ball_clear();
        ball_col++; 
      }
      if(prev==20)
      {
        randomSeed(RANDOM_PARAMETER);
        prev=random(1,3);
      }
      if(prev==1)
      ball_loc=6;
      else
      ball_loc=1;
      prev=5;
      ball();
      break;
      case 6:
      if(player==0)
      {
        ball_clear();
        ball_col--; 
      }
      if(prev==5)
      ball_loc=10;
      else
      ball_loc=5;
      prev=6;
      ball();
      break;
      case 9:
      if(player)
      {
        ball_clear();
        ball_col++; 
      }
      if(prev==2)
      ball_loc=7;
      else
      ball_loc=2;
      prev=9;
      ball();
      break;
      case 7:
      if(player==0)
      {
        ball_clear();
        ball_col--; 
      }
      if(prev==9)
      ball_loc=11;
      else
      ball_loc=9;
      prev=7;
      ball();
      break;
      case 10:
      if(player)
      {
        ball_clear();
        ball_col++; 
      }
      if(prev==6)
      ball_loc=8;
      else
      ball_loc=6;
      prev=10;
      ball();
      break;
      case 8:
      if(player==0)
      {
        ball_clear();
        ball_col--; 
      }
      ball_loc=10;
      prev=8;
      ball();
      break;
      case 11:
      if(player)
      {
        ball_clear();
        ball_col++; 
      }
      ball_loc=7;
      prev=11;
      ball();
      break;
    } 
  }
  else
   ball_cnt++; 
}

//to declare a winner on lcd
void win(unsigned char i)
{
  lcd.clear();
  lcd.setCursor(0,0);
  if(i)
  lcd.print("Player 2 Wins!");
  else
  lcd.print("Player 1 Wins!");
  delay(2000);
  initial();
}

//to control movement of player 2 pad
void pad1_run(unsigned char i)
{
  if(sens_pad1==SENSITIVITY_PAD)
  {
    if(pad1==0)
     pad1=1; 
    if(i)
     pad1--; 
    else
     pad1++; 
    if(pad1==10)
     pad1=9; 
    pad1_print();
    sens_pad1=0; 
  }
  sens_pad1++;
}

//to control movement of player 1 pad
void pad0_run(unsigned char i)
{
  if(sens_pad0==SENSITIVITY_PAD)
  {
    if(pad0==0)
     pad0=1;  
    if(i)
     pad0--;  
    else
     pad0++; 
    if(pad0==10)
     pad0=9;  
    pad0_print(); 
    sens_pad0=0;
  }
  sens_pad0++;
}
