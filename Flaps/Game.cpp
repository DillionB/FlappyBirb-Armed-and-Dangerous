#include "raylib.h"
#include <cmath>
#include <string>
#include <fstream>

typedef enum{
    STORAGE_POSITION_HISCORE = 1
} storageData;

int main()
{
    // set screen dimensions
    int screenWidth{1000};
    int screenHeight{600};

    // initiate window and set background texture
    InitWindow(screenWidth,screenHeight, "mywindow");
    Texture2D Back = LoadTexture("textures/flapBack.png");
    Texture2D ground1 = LoadTexture("textures/ground.png");
    Texture2D GameOver = LoadTexture("textures/over.png");
    Texture2D Medal = LoadTexture("");;
    float Gx = 0;
    bool Start{};
    bool gOver {};// gameover
      
    // initialize player pawn variables
    Texture2D Flappy = LoadTexture("textures/flap1.png");
    Rectangle FlappyRec {0, 0, Flappy.width,Flappy.height };
       
    Vector2 FlappyPos{screenWidth/6 - FlappyRec.width/2, screenHeight/2 - FlappyRec.height};
    int Velocity{5}; 
    int playerScore{0};
    int highScore{};

    // initialize player weapon variables
    Texture2D Gun = LoadTexture("textures/flapGun2.png");
    Rectangle GunRec;
        GunRec.width = Gun.width;
         GunRec.height = Gun.height;
        GunRec.x = 0;
        GunRec.y = 0;
    
    // initialize Weapon Crosshair variables
    Texture2D Cross = LoadTexture("textures/crosshair.png");
    Rectangle CrossRec;
        CrossRec.width = Cross.width;
        CrossRec.height = Cross.height;
        CrossRec.x = 0;
        CrossRec.y = 0;

    //set bullet variables 
    float cX;
    float cy;
    float bx;   
    float by;
    float length;
    bool fire;

    // set Enemy variables
    Texture2D fly = LoadTexture("textures/redFlap.png");
    Rectangle FlyRec; 
    Vector2 flyV{1000.0f, 0.0f};  
        FlyRec.width = 52;
        FlyRec.height = 54;
        FlyRec.x=0;
        FlyRec.y = 0;
    bool dead{};
    bool up{};


    //set Pipe Bottom variables
    Texture2D pipe = LoadTexture("textures/pipe.png");
    Texture2D pipeTop = LoadTexture("textures/pipe2.png");
    Rectangle pipeRec; 
    Vector2 pipeV;
    pipeRec.width = pipe.width;
    pipeRec.height = pipe.height;
    pipeRec.x=0;
    pipeRec.y = 0;
    pipeV.x=1400;
    pipeV.y = 400;
    Vector2 pipeTV{pipeV.x, pipeV.y -600};  

    //set Pipe Bottom 2 variables
    Texture2D pipe2 = LoadTexture("textures/pipe.png");
    Rectangle pipe2Rec;   
    Vector2 pipe2V;
    pipe2Rec.width = pipe.width;
    pipe2Rec.height = pipe.height;
    pipe2Rec.x=0;
    pipe2Rec.y = 0;
    pipe2V.x=1000;
    pipe2V.y = 400;
    Vector2 pipe2TV{pipe2V.x, pipe2V.y -600}; 
    
    //set Pipe Bottom 3 variables
    Texture2D pipe3 = LoadTexture("textures/pipe.png");
    Rectangle pipe3Rec;   
    Vector2 pipe3V;
    pipe3Rec.width = pipe.width;
    pipe3Rec.height = pipe.height;
    pipe3Rec.x=0;
    pipe3Rec.y = 0;
    pipe3V.x=1000;
    pipe3V.y = 400;
    Vector2 pipe3TV{pipe3V.x, pipe3V.y -600}; 
    

    
    SetTargetFPS(60);
    while (WindowShouldClose()==false)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(Back, 0, 0, WHITE);

        // loop ground texture
        DrawTexture(ground1, Gx, 450, WHITE);
        DrawTexture(ground1, Gx+ 1000, 450, WHITE);
        Gx -=3;
        if (Gx <= -1000.0)
        {
             Gx = 0;
        }; 

        DrawTextureRec(Flappy, FlappyRec, FlappyPos, WHITE);
         // get mouse coordinates
        Vector2 mxy = GetMousePosition();
        int mx = mxy.x;
        int my = mxy.y;

        

        //Draw Crosshair
        DrawTextureRec(Cross, CrossRec,mxy, WHITE);
        
        // calculate weapon rotation from mouse coords
        
        float adj = sqrt(pow((FlappyPos.x - mx), 2) + pow((FlappyPos.y - my), 2));
        float opp = my - FlappyPos.y;
        float ang = opp/adj;
        float rot = (asin(ang))*180;
        //Draw Weapon
        Rectangle dest {FlappyPos.x + 30, FlappyPos.y + 25, GunRec.width, GunRec.height};
        DrawTexturePro(Gun, GunRec, dest, {}, rot, WHITE); 
        
        
        // draw ready screen
        Texture2D Ready = LoadTexture("textures/start.png");
        
        
        
        
        float Rx = 300;
        float Ry= 100;

        
       

        
        

        // set menu card Gameover/start game
        if (gOver)
        {
            highScore = LoadStorageValue(STORAGE_POSITION_HISCORE); //load high score
            
            if (playerScore>highScore){highScore=playerScore;GameOver=LoadTexture("textures.newOver.png");}
            else   GameOver = LoadTexture("textures/over.png");
            if (playerScore > 1) {Medal=LoadTexture("textures/bronze.png");}
            if (playerScore > 2) {Medal=LoadTexture("textures/silver.png");}
            if (playerScore > 3) {Medal=LoadTexture("textures/gold.png");}
                SaveStorageValue(STORAGE_POSITION_HISCORE, highScore);
                DrawTexture(GameOver, Rx, Ry, WHITE);
                DrawTexture(Medal, Rx, Ry, WHITE); 
                std::string Score = std::to_string(playerScore); 
                DrawText(Score.c_str(), 580.f,230.f,40,WHITE);
                std::string hScore = std::to_string(highScore); 
                DrawText(hScore.c_str(), 580.f,280.f,40,WHITE);
            if (IsKeyPressed(KEY_SPACE))
                {gOver=false; FlappyPos.y=300; playerScore=0;
                 pipeV.x=1000; pipe2V.x=1000; pipe3V.x=1000; 
                 pipeTV.x=1000; pipe2TV.x=1000; pipe3TV.x=1000;
                }
        }

        else
         {
            if (!Start){DrawTexture(Ready, Rx, Ry, WHITE);}
            // start game
            if (!Start){ if (IsKeyPressed(KEY_SPACE)){Start=true;};};
         };
        
     if (Start) 
     {
        DrawTextureRec(fly, FlyRec, flyV, WHITE);
        if (dead)
        {
            flyV.y+=3;
        }
         flyV.x -= 3;
         if (CheckCollisionPointRec(FlappyPos, FlyRec) ){gOver=true; Start=false;flyV.x=1000;}
          
         if (flyV.x < -200){flyV.x=1000;}
         if (flyV.y > 800){flyV.x=0;}
         if (flyV.y >250 ){up = true;}
         if (flyV.y <20 ){up = false;}
         if (up == true){flyV.y-=3;}
         else flyV.y+=3;


        // if player is jumping, apply downward force over time[gravity]
        if (Velocity < 5)
        {
            Velocity += 1;

        }

        //jump by applying upward velocity, and check velocity before allowing additional jump
        if (IsKeyPressed(KEY_SPACE) && Velocity > 4)
        {
            Velocity = -20;
            
        }

        // set texture for jumping or falling
        Velocity < 5 ? Flappy = LoadTexture("textures/flap2.png") 
            :Flappy = LoadTexture("textures/flap1.png");
        
     
        // set player and weapon posistions      
        FlappyPos.y += Velocity;
        

       

        //Draw Score
        std::string Score = "Score:";
        Score.append(std::to_string(playerScore),0,5);
        DrawText(Score.c_str(), 55.f,45.f,40,WHITE);
        
        

        
        
        //Draw Crosshair
        DrawTextureRec(Cross, CrossRec,mxy, WHITE); 

       
        
        

        //draw Pipe
        if (pipeV.x == FlappyPos.x) {playerScore+=1;}
        
        pipeV.x-=5;
        DrawTextureRec(pipe, pipeRec,pipeV, WHITE);
        pipeTV.x-=5;
        DrawTextureRec(pipeTop, pipeRec,pipeTV, WHITE);
        if (pipeV.x == FlappyPos.x && FlappyPos.y > pipeV.y ){Start = false; gOver = true;}
        if (pipeTV.x == FlappyPos.x && FlappyPos.y < pipeV.y-200  ){Start = false; gOver = true;}
        
        if (pipeV.x < -700 ) {pipeV.x=1000; pipeV.y = GetRandomValue(200,450) ;} 
        if (pipeTV.x < -700 ) {pipeTV.x=1000; pipeTV.y = pipeV.y -600;} 
        

        //draw pipe 2
        if (pipeV.x <700) {
            if (pipe2V.x == FlappyPos.x) {playerScore+=1;}
            pipe2V.x-=5;
        DrawTextureRec(pipe2, pipe2Rec,pipe2V, WHITE);
        pipe2TV.x-=5;
        DrawTextureRec(pipeTop, pipe2Rec,pipe2TV, WHITE);
        if (pipe2V.x == FlappyPos.x && FlappyPos.y > pipe2V.y ){Start = false; gOver = true;}
        if (pipe2TV.x == FlappyPos.x && FlappyPos.y < pipe2V.y-200  ){Start = false; gOver = true;}
        if (pipe2V.x < -700 ) {pipe2V.x=1000;} 
        if (pipe2TV.x < -700 ) {pipe2TV.x=1000;} 
        }

        //draw pipe 3
        if (pipe2V.x <800) {
            if (pipe3V.x == FlappyPos.x) {playerScore+=1;}
            pipe3V.x-=5;
        DrawTextureRec(pipe3, pipe3Rec,pipe3V, WHITE);
        pipe3TV.x-=5;
        DrawTextureRec(pipeTop, pipe3Rec,pipe3TV, WHITE);
        if (pipe3V.x == FlappyPos.x && FlappyPos.y > pipe3V.y ){Start = false; gOver = true;}
        if (pipe3TV.x == FlappyPos.x && FlappyPos.y < pipe3V.y-200  ){Start = false; gOver = true;}
        if (pipe3V.x < -700 ) {pipe3V.x=1000; pipe3V.y = GetRandomValue(200,450);} 
        if (pipe3TV.x < -700 ) {pipe3TV.x=1000; pipe3TV.y = pipe3V.y -600;} 
        }
        //fire weapon
        
       
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            cX= mx - FlappyPos.x;
            cy= my - FlappyPos.y;
            length = sqrtf(cX*cX+cy*cy);
            cX/=length ;
            cy/=length ;
            fire = true;
            by= FlappyPos.x;
            bx= FlappyPos.y;
        }
        // set speed and bullet pos
        if (fire)
        {
            bx+= cX *10;
            by+= cy *10;
                Vector2 bullV{bx,by};
                Texture2D bull = LoadTexture("textures/bull.png");
                Rectangle bullRec{0,0,bull.width,bull.height};
                DrawTextureRec (bull, bullRec,bullV, RED);
                if (CheckCollisionPointRec(bullV, FlyRec)){dead=true;}
        }
     }
        HideCursor(); 

        EndDrawing();
    }
}