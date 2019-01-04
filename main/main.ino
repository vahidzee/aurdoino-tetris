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

        //Joystick Pins
        #define JYS_X_PIN 0
        #define JYS_Y_PIN 1
        #define JYS_BTN_PIN 3
        #define JYS_VCC_PIN 5

        //Screen Size
        #define DEVICE_WIDTH 8
        #define DEVICE_HEIGHT 8

        #define SCREEN_HEIGHT 16
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
    LedControl led_controller = LedControl(SCREEN_DIN_PIN,SCREEN_CLK_PIN,SCREEN_CS_PIN,0);

    bool bottom_chunk[SCREEN_WIDTH][SCREEN_HEIGHT] = {false};
    Block live_block;
    int loop_counter = 0;
//Functions
    //Setup & Init Functions
        void init_led_controller() {
        for(int index=0;index<led_controller.getDeviceCount();index++) {
            //The MAX72XX is in power-saving mode on startup/
            led_controller.shutdown(index,false);
            /* Set the brightness to a medium values */
            led_controller.setIntensity(index,0);
            /* and clear the display */
            led_controller.clearDisplay(index);
            }
        }

        void init_joy_stick() {
            pinMode(JYS_VCC_PIN, OUTPUT );
            digitalWrite(JYS_VCC_PIN, HIGH);

            pinMode(JYS_BTN_PIN, INPUT );
        }
    
    //Screen Methods
    void show_screen_for_map( bool pixels[SCREEN_WIDTH][SCREEN_HEIGHT] ) {
        short deviceNumber = 0;
        for( int y = 0;y < SCREEN_HEIGHT;y++){
            deviceNumber = y/DEVICE_HEIGHT;
            for( int x = 0; x < DEVICE_WIDTH ;  x++ ){
                led_controller.setLed( deviceNumber ,  DEVICE_WIDTH - x - 1, DEVICE_HEIGHT - y - 1 + deviceNumber * DEVICE_HEIGHT , pixels[x][y] );
            } 
        }
    }

    void show_game_map( ) {
        bool map[SCREEN_WIDTH][SCREEN_HEIGHT];
        for( int x = 0 ; x <SCREEN_WIDTH ; x++ )
            for( int y = 0 ; y < SCREEN_HEIGHT ; y++ )
                map[x][y] = bottom_chunk[x][y];
        for( int i = 0 ; i < 4 ; i++ ) {
            map[live_block.points[i].x][live_block.points[i].y] = true; 
        }
        show_screen_for_map(map);
    }

    void show_load_screen() {
        byte G[] = {B00000000,B00111110,B00100000,B00101110,B00100010,B00100010,B00111110,B00000000};
        byte A[] = {  B00000000,B00111100,B01000010,B01000010,B01111110,B01000010,B01000010,0};
        byte M[] = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
        byte E[] = {B00000000,B01111110,B01000000,B01111000,B01000000,B01000000,B01111110,B00000000};
        
        //Clearing Displays
        for(int i = 0; i < led_controller.getDeviceCount() ; i++ )
            led_controller.clearDisplay(i);

        for(int i = 0;i<8;i++){
            led_controller.setRow(3,i,G[i]);
        }

        for(int i = 0;i<8;i++){
            led_controller.setRow(2,i,A[i]);   
        }

        for(int i = 0;i<8;i++){
            led_controller.setRow(1,i,M[i]);
        }

        for(int i = 0;i<8;i++){
            led_controller.setRow(0,i,E[i]);
        }

        delay(5000);
        //Clearing Displays
        for(int i = 0; i < led_controller.getDeviceCount() ; i++ )
            led_controller.clearDisplay(i);

    }
    //Live Block Interactions
    bool live_block_reached_bottom_chunck(){
        for( int i = 0 ; i < 4 ; i++ )
            if( live_block.points[i].y == 0 || bottom_chunk[live_block.points[i].x][live_block.points[i].y - 1] == true )
                return true;
        return false;
    }

    void register_live_block_to_bottom_chunck() {
        for( int i = 0 ; i < 4 ; i++ )
            bottom_chunk[live_block.points[i].x][live_block.points[i].y] = true;
    }

    //Live Block Movements
    void move_live_block_left() {
        for( int i = 0 ; i < 4 ; i++ ) {
            if( live_block.points[i].x == 0 || bottom_chunk[live_block.points[i].x-1][live_block.points[i].y] )
                return;  
        }
        for( int i = 0 ; i < 4 ; i++ ) 
            live_block.points[i].x--;
    }

    void move_live_block_right(){
        for( int i = 0 ; i < 4 ; i++ ) {
            if( live_block.points[i].x == SCREEN_WIDTH - 1 || bottom_chunk[live_block.points[i].x+1][live_block.points[i].y] )
                return;  
        }
        for( int i = 0 ; i < 4 ; i++ ) 
            live_block.points[i].x++;
    }

    void move_live_block_down() {
        if( !live_block_reached_bottom_chunck() )
            for( int i = 0 ; i < 4 ; i++ ) 
                live_block.points[i].y--;
    }

    void rotatelive_block() {
        //Linear Shape
        if(live_block.type == 0) {
            //Vertical
            if(live_block.points[0].x == live_block.points[1].x) {
                int newY = live_block.points[2].y ;
                int newX = live_block.points[2].x;

                for(int i = 0 ; i < 4; i++)
                    live_block.points[i].y = newY;

                live_block.points[3].x = newX - 1;
                live_block.points[1].x = newX +1;
                live_block.points[0].x = newX +2; 

                return;
            }
            //Horizontal
            if(live_block.points[0].y == live_block.points[1].y)  {
                int newX = live_block.points[1].x;
                int newY = live_block.points[1].y;

                for(int i = 0 ; i < 4; i++)
                    live_block.points[i].x = newX;

                live_block.points[0].y = newY + 1;
                live_block.points[2].y = newY -1 ;
                live_block.points[3].y = newY - 2;   

                return;
            } 
        }
            
        //T & L Shapes
        if(live_block.type ==2 || live_block.type == 3 || live_block.type == 4 ){
            for( int i = 0 ; i < 4 ; i++ ){
                int prev_x = live_block.points[i].x;
                int prev_y = live_block.points[i].y;
                live_block.points[i].x  = prev_y   -  live_block.points[1].y +live_block.points[1].x ;
                live_block.points[i].y = -prev_x  + live_block.points[1].x + live_block.points[1].y ;
            }
            return;
        }

        if(live_block.type == 5) {
            int newX = live_block.points[2].x;
            int newY = live_block.points[2].y;
            
            if(live_block.points[1].y == live_block.points[3].y) {
                live_block.points[3].x = newX + 1;
                live_block.points[3].y = newY - 1;
            }
            else if(live_block.points[0].x == live_block.points[3].x){
                live_block.points[3].x = newX - 1;
                live_block.points[3].y = newY + 1;
            }
        }
    }

    //Game Logic
    void start_new_game() {
        show_load_screen();

        //Clearing bottom chunck
        for(int i = 0; i < SCREEN_WIDTH; i++ )
            for(int j = 0; j < SCREEN_HEIGHT; j++ )
                bottom_chunk[i][j] = false;

        generate_new_live_block();
        loop_counter = 0;
    }

    void generate_new_live_block( ){
        live_block.type = rand() % 6 ;
        if(live_block.type== 0)   {
            live_block.points[0].x = 4;
            live_block.points[1].x = 4;
            live_block.points[2].x = 4;
            live_block.points[3].x = 4;
            live_block.points[0].y = SCREEN_HEIGHT - 1;
            live_block.points[1].y = SCREEN_HEIGHT - 2;
            live_block.points[2].y = SCREEN_HEIGHT - 3;
            live_block.points[3].y = SCREEN_HEIGHT - 4;
        }
        else if(live_block.type == 1){
            live_block.points[0].x = 3;
            live_block.points[1].x = 3;
            live_block.points[2].x = 4;
            live_block.points[3].x = 4;
            live_block.points[0].y = SCREEN_HEIGHT - 1;
            live_block.points[1].y = SCREEN_HEIGHT - 2;
            live_block.points[2].y = SCREEN_HEIGHT - 1;
            live_block.points[3].y = SCREEN_HEIGHT - 2;
        }
        else if(live_block.type== 2)
        {
            live_block.points[0].x = 3;
            live_block.points[1].x = 4;
            live_block.points[2].x = 5;
            live_block.points[3].x = 3;
            live_block.points[0].y = SCREEN_HEIGHT - 1;
            live_block.points[1].y = SCREEN_HEIGHT - 2;
            live_block.points[2].y = SCREEN_HEIGHT - 2;
            live_block.points[3].y = SCREEN_HEIGHT - 2;

        }
        else if(live_block.type == 3){
            live_block.points[0].x = 4;
            live_block.points[1].x = 4;
            live_block.points[2].x = 5;
            live_block.points[3].x = 3;

            live_block.points[0].y = SCREEN_HEIGHT - 1;
            live_block.points[1].y = SCREEN_HEIGHT - 2;
            live_block.points[2].y = SCREEN_HEIGHT - 2;
            live_block.points[3].y = SCREEN_HEIGHT - 2;
        }
        else if(live_block.type == 4){
            live_block.points[0].x = 5;
            live_block.points[1].x = 4;
            live_block.points[2].x = 5;
            live_block.points[3].x = 3;
            live_block.points[0].y = SCREEN_HEIGHT - 1;
            live_block.points[1].y = SCREEN_HEIGHT - 2;
            live_block.points[2].y = SCREEN_HEIGHT - 2;
            live_block.points[3].y = SCREEN_HEIGHT - 2;
        }
        else if(live_block.type == 5){
            live_block.points[0].x = 5;
            live_block.points[1].x = 4;
            live_block.points[2].x = 4;
            live_block.points[3].x = 3;
            live_block.points[0].y = SCREEN_HEIGHT - 2;
            live_block.points[1].y = SCREEN_HEIGHT - 1;
            live_block.points[2].y = SCREEN_HEIGHT - 2;
            live_block.points[3].y = SCREEN_HEIGHT - 1;
        }
    }

    void remove_full_bottom_rows( )  { 
        short counter = 0;
        short full_count = 0;
        short y  = 0;
        for(;  y < SCREEN_HEIGHT; y++ ){
            short x = 0;
            for( ; x < SCREEN_WIDTH; x++ )
                if( !bottom_chunk[x][y] )
                    break;
            if( x != SCREEN_WIDTH && full_count > 0 ){
                break;
            }
            if( x == SCREEN_WIDTH ){
                full_count++;
                for(short x = 0; x < SCREEN_WIDTH; x++ )
                    bottom_chunk[x][y] = false;
            }
        }
        if( full_count ){
            for(y-=full_count ; y < SCREEN_HEIGHT - full_count; y++ )
                for(short x = 0; x < SCREEN_WIDTH; x++ )
                    bottom_chunk[x][y] = bottom_chunk[x][y+full_count];
            for(; y < SCREEN_HEIGHT; y++ )
                for(short x = 0; x < SCREEN_WIDTH; x++ )
                    bottom_chunk[x][y] = false;        
        }
            
    }

    
    //Action Handlings
    void getAction() {
        int x = analogRead(JYS_X_PIN);

        int y = analogRead(JYS_Y_PIN);
        
        //Left
        if( x < 500 && y < 612 && y > 412 ){
            move_live_block_left();
            return;
        }

        //Right
        if( x > 520 && y < 612 && y > 412 ){
            move_live_block_right();
            return;
        }

        //Down
        if( y < 300 ){
            move_live_block_down();
            return;
        }
        //Up -> Rotate
        if( y > 650 ) 
            rotatelive_block();
    }

//Main
    void setup(){
        init_joy_stick();
        init_led_controller();
        
        start_new_game();
    }

    
    void loop(){ 
        loop_counter++;
        if( loop_counter == 3 ) {
            loop_counter = 0;
            move_live_block_down();
        } 
        getAction();
        show_game_map();
        if( live_block_reached_bottom_chunck() ) {
            register_live_block_to_bottom_chunck();
            remove_full_bottom_rows();
            show_game_map();
            generate_new_live_block();
            show_game_map();
            if(live_block_reached_bottom_chunck()){
                delay(1000);
                start_new_game();
            }
        }
    }
