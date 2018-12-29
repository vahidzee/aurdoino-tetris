//Including External Libraries
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

        #define SCREEN_HEIGHT 24 
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
        for( int y = 0;y < SCREEN_HEIGHT;y++, deviceNumber = y/DEVICE_HEIGHT){
            for( int x = 0; x < DEVICE_WIDTH ;  x++ ){
                ledController.setLed( deviceNumber , DEVICE_HEIGHT - y - 1, DEVICE_WIDTH - x - 1 , pixels[x][y] );
            } 
        }
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
    bool isGameFinished( ) { /*  TODO jame live block va bottomChunk kolle safaro por kone */
        return false;
    }

    void removeFullBottomRows( )  { 

    }

    void moveLiveBlockLeft() {

    }
    void moveLiveBlockRight(){

    }

    void rotateLiveBlock() {

    }

    void moveLiveBlockDown() { /* one step */

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

        liveBlock.points[0].x = 0;
        liveBlock.points[1].x = 0;
        liveBlock.points[2].x = 0;
        liveBlock.points[3].x = 0;

        liveBlock.points[0].y = 15;
        liveBlock.points[1].y = 14;
        liveBlock.points[2].y = 13;
        liveBlock.points[3].y = 12;
    }

    void loop(){ 
        showGameMap();
        getAction();

    }
