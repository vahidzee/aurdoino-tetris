#include <time.h>
#include<stdlib.h>
#include <LedControl.h>


//Defining Constant Values & Handles
    //Handles
    //Constant Values
        //Screen Pins
        #define SCREEN_DIN_PIN 2
        #define SCREEN_CS_PIN 1
        #define SCREEN_CLK_PIN 0

        //Button Pins
        #define BTN_LEFT_PIN 6
        #define BTN_RIGHT_PIN 5
        #define BTN_DOWN_PIN 4
        #define BTN_ROTATE_PIN 3

        //Screen Size
        #define DEVICE_WIDTH 8
        #define DEVICE_HEIGHT 8

        #define SCREEN_HEIGHT 32
        #define SCREEN_WIDTH 8

        //INPUT_TYPE


//Defining Structures
    //Structures
    typedef struct {
        byte x,y;
    } Point;

    typedef struct {
        Point points[4];
        short type;
    } Block;

    



int randomNumber;


//Global Variables
    LedControl ledController = LedControl(SCREEN_DIN_PIN,SCREEN_CLK_PIN,SCREEN_CS_PIN,0);

    bool bottomChunck[SCREEN_WIDTH][SCREEN_HEIGHT] = {false};
    Block liveBlock;

//Functions
    //Setup & Init Functions
        void init_ledController() {
        for(int index=0;index<ledController.getDeviceCount();index++) {
            /*The MAX72XX is in power-saving mode on startup*/
            ledController.shutdown(index,false);
            /* Set the brightness to a medium values */
            ledController.setIntensity(index,0);
            /* and clear the display */
            ledController.clearDisplay(index);
            }
        }
        void init_buttons() {
            pinMode(BTN_LEFT_PIN, INPUT );
            pinMode(BTN_RIGHT_PIN, INPUT );
            pinMode(BTN_DOWN_PIN, INPUT );
            pinMode(BTN_ROTATE_PIN, INPUT );
        }
    
    //Screen Methods
    void showScreenForMap( bool pixels[SCREEN_WIDTH][SCREEN_HEIGHT] ) {
        short deviceNumber = 0;
        for( int y = 0;y < SCREEN_HEIGHT;y++){
            deviceNumber = y/DEVICE_HEIGHT;
            for( int x = 0; x < DEVICE_WIDTH ;  x++ ){
                ledController.setLed( deviceNumber ,  DEVICE_WIDTH - x - 1, DEVICE_HEIGHT - y - 1 + deviceNumber * DEVICE_HEIGHT , pixels[x][y] );
            } 
        }
    }


    //Live Block Interactions
    bool live_block_reached_bottom_chunck(){
        for( int i = 0 ; i < 4 ; i++ )
            if( liveBlock.points[i].y == 0 || bottomChunck[liveBlock.points[i].x][liveBlock.points[i].y - 1] == true )
                return true;
        return false;
    }

    void register_live_block_to_bottom_chunck() {
        for( int i = 0 ; i < 4 ; i++ )
            bottomChunck[liveBlock.points[i].x][liveBlock.points[i].y] = true;
    }

    void showGameMap( ) {
        bool map[SCREEN_WIDTH][SCREEN_HEIGHT];
        for( int x = 0 ; x <SCREEN_WIDTH ; x++ )
            for( int y = 0 ; y < SCREEN_HEIGHT ; y++ )
                map[x][y] = bottomChunck[x][y];
        for( int i = 0 ; i < 4 ; i++ ) {
            map[liveBlock.points[i].x][liveBlock.points[i].y] = true; 
        }
        showScreenForMap(map);
    }
    //Game Logic
    void generate_new_live_block( ){
      
        liveBlock.type = rand() % 6 ;
         
        if(liveBlock.type== 0)   {
            liveBlock.points[0].x = 4;
            liveBlock.points[1].x = 4;
            liveBlock.points[2].x = 4;
            liveBlock.points[3].x = 4;
            liveBlock.points[0].y = SCREEN_HEIGHT - 1;
            liveBlock.points[1].y = SCREEN_HEIGHT - 2;
            liveBlock.points[2].y = SCREEN_HEIGHT - 3;
            liveBlock.points[3].y = SCREEN_HEIGHT - 4;
        }
        else if(liveBlock.type == 1){
            liveBlock.points[0].x = 3;
            liveBlock.points[1].x = 3;
            liveBlock.points[2].x = 4;
            liveBlock.points[3].x = 4;
            liveBlock.points[0].y = SCREEN_HEIGHT - 1;
            liveBlock.points[1].y = SCREEN_HEIGHT - 2;
            liveBlock.points[2].y = SCREEN_HEIGHT - 1;
            liveBlock.points[3].y = SCREEN_HEIGHT - 2;
        }
        else if(liveBlock.type== 2)
        {
            liveBlock.points[0].x = 3;
            liveBlock.points[1].x = 4;
            liveBlock.points[2].x = 5;
            liveBlock.points[3].x = 3;
            liveBlock.points[0].y = SCREEN_HEIGHT - 1;
            liveBlock.points[1].y = SCREEN_HEIGHT - 2;
            liveBlock.points[2].y = SCREEN_HEIGHT - 2;
            liveBlock.points[3].y = SCREEN_HEIGHT - 2;

        }

        else if(liveBlock.type == 3){
            liveBlock.points[0].x = 4;
            liveBlock.points[1].x = 4;
            liveBlock.points[2].x = 5;
            liveBlock.points[3].x = 3;

            liveBlock.points[0].y = SCREEN_HEIGHT - 1;
            liveBlock.points[1].y = SCREEN_HEIGHT - 2;
            liveBlock.points[2].y = SCREEN_HEIGHT - 2;
            liveBlock.points[3].y = SCREEN_HEIGHT - 2;
        }
        else if(liveBlock.type == 4){
            liveBlock.points[0].x = 5;
            liveBlock.points[1].x = 4;
            liveBlock.points[2].x = 5;
            liveBlock.points[3].x = 3;
            liveBlock.points[0].y = SCREEN_HEIGHT - 1;
            liveBlock.points[1].y = SCREEN_HEIGHT - 2;
            liveBlock.points[2].y = SCREEN_HEIGHT - 2;
            liveBlock.points[3].y = SCREEN_HEIGHT - 2;
        }
        else if(liveBlock.type == 5){
            liveBlock.points[0].x = 5;
            liveBlock.points[1].x = 4;
            liveBlock.points[2].x = 4;
            liveBlock.points[3].x = 3;
            liveBlock.points[0].y = SCREEN_HEIGHT - 2;
            liveBlock.points[1].y = SCREEN_HEIGHT - 1;
            liveBlock.points[2].y = SCREEN_HEIGHT - 2;
            liveBlock.points[3].y = SCREEN_HEIGHT - 1;
        }
    }


    bool isGameFinished( ) { /*  TODO jame live block va bottomChunk kolle safaro por kone */
        return false;
    }

    void removeFullBottomRows( )  { 

    }

    void moveLiveBlockLeft() {
      short min = liveBlock.points[0].x;
      for( int i = 0 ; i < 4 ; i++ ) 
        min = ( liveBlock.points[i].x < min ) ? liveBlock.points[i].x : min;
      if( min > 0 )
        for( int i = 0 ; i < 4 ; i++ ) 
          liveBlock.points[i].x--;
    }
    void moveLiveBlockRight(){
      short max = liveBlock.points[0].x;
      for( int i = 0 ; i < 4 ; i++ ) 
        max = ( liveBlock.points[i].x > max ) ? liveBlock.points[i].x : max;
      if( max < SCREEN_WIDTH - 1 )
        for( int i = 0 ; i < 4 ; i++ ) 
          liveBlock.points[i].x++;
    }

    void rotateLiveBlock() {
      // #####
      if(liveBlock.type == 0) {
        if(liveBlock.points[0].x == liveBlock.points[1].x) {
          // amoodi
          int newY = liveBlock.points[2].y ;
          for(int i = 0 ; i < 4; i++)
          liveBlock.points[i].y = newY;
          int newX = liveBlock.points[2].x;
          liveBlock.points[3].x = newX - 1;
          liveBlock.points[1].x = newX +1;
          liveBlock.points[0].x = newX +2;  }
        else if(liveBlock.points[0].y == liveBlock.points[1].y)  {
          //ofoghi
          int newX = liveBlock.points[1].x;
           for(int i = 0 ; i < 4; i++)
          liveBlock.points[i].x = newX;
          int newY = liveBlock.points[1].y;
          liveBlock.points[0].y = newY + 1;
          liveBlock.points[2].y = newY -1 ;
          liveBlock.points[3].y = newY - 2;   
          } 
      }

      else if(liveBlock.type == 1)  
        return;

      else if(liveBlock.type ==2){

        // for( int i = 0 ; i < 4 ; i++ ){
        //     int perv_x = liveBlock.points[i].x;
        //     int perv_y = liveBlock.points[i].y;

        //     liveBlock.points[i].x = -

        // }
        
       
        
        
        
      }

      else if(liveBlock.type == 3) {
        int newX =  liveBlock.points[1].x;
        int newY =  liveBlock.points[1].y;
        if(liveBlock.points[0].x == liveBlock.points[1].x) {
          
          liveBlock.points[3]. x = newX;
          liveBlock.points[3].y = newY - 1;
          
        }
        else if(liveBlock.points[2].y == liveBlock.points[1].y)
        { 
          liveBlock.points[0]. x = newX - 1;
          liveBlock.points[0].y = newY ;
          
        }
        else if(liveBlock.points[3].x == liveBlock.points[1].x){
          liveBlock.points[2]. x = newX ;
          liveBlock.points[2].y = newY  + 1;
        }
        else if( liveBlock.points[0].y == liveBlock.points[1].y){
           liveBlock.points[3]. x = newX + 1;
          liveBlock.points[3].y = newY ;
          
        }
        
      }
      else if(liveBlock.type == 4){
        
      }
      else if(liveBlock.type == 5) {
        int newX = liveBlock.points[2].x;
        int newY = liveBlock.points[2].y;
        
        if(liveBlock.points[1].y == liveBlock.points[3].y) {
        liveBlock.points[3].x = newX + 1;
        liveBlock.points[3].y = newY - 1;
          
        }
        else if(liveBlock.points[0].x == liveBlock.points[3].x){
            liveBlock.points[3].x = newX - 1;
            liveBlock.points[3].y = newY + 1;
        }
       
      }
      
    }

    void moveLiveBlockDown() { /* one step */
      for( int i = 0 ; i < 4 ; i++ ) 
        liveBlock.points[i].y--;
    }


    //Action Handling
    void getAction() {
        if( digitalRead(BTN_LEFT_PIN) == HIGH )
            moveLiveBlockLeft();
        if( digitalRead(BTN_RIGHT_PIN) == HIGH )
            moveLiveBlockRight();
        if( digitalRead(BTN_ROTATE_PIN) == HIGH )
            rotateLiveBlock();
        if( digitalRead(BTN_DOWN_PIN) == HIGH )
            moveLiveBlockDown();
    }

//Main
    void setup(){
        init_ledController();
        init_buttons();
        generate_new_live_block();
        // randomSeed(second());
//         Serial.begin(9600);
//          randomSeed(second()); // nothing connected to 0 so read sees noise
   
    }

    void loop(){ 
        showGameMap();
        getAction();
        moveLiveBlockDown();
        delay(200);
        if( live_block_reached_bottom_chunck() ) {
            register_live_block_to_bottom_chunck();
            generate_new_live_block();
        }
            
         
        
    }

