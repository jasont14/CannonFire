#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

//Introductory script
int StartUp(){

    cout << endl << "Welcome to Cannon Fire. " << endl;
    cout << "You are in the middle of a war and being charged by thousands of enemies." << endl;
    cout << "You have one cannon, which you can shoot at any angle." << endl;
    cout << "You only have 10 cannonballs for this target.." << endl;
    cout << "Let's begin..." << endl << endl;    
    return 0;

}

int GetEnemyPosition(){

    int result;

    cout << "I found an enemy." << endl;

    srand(time(NULL));
    result = rand() % 1242 + 1;
    return result;
}

int GetAngleFromUser(){

    int result;
    bool success = false;    

    //Get user input and validate.
    do {
   
        cout << "What angle should we set the cannon? ";
        if (!(cin >> result )){

        cout << endl << "You entered a non numeric.  Please enter angle." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        continue;
        }

        success = true;

    } while (!success);

    return result;

}

int CalculateShot(int angle){

    int result;

    double velocity = 200.0;    //Initial velocity of cannon in ft/sec
    double gravity = 32.2;      //Gravity constant  ft/s^2

    double time_in_air = (2.0 * velocity * sin(angle * 3.14 / 180)) / gravity;
    int distance = round((velocity * cos(angle * 3.14 / 180)) * time_in_air);

}

bool DetermineShotSuccess(int shotResult, int enemyPosition, int killRadius)
{   
    bool result = false;

    int shotVEnemy = abs(shotResult - enemyPosition);

    if (shotVEnemy <= killRadius)
    {
        result = true;
    }

    return result;

}


void DisplayShotResults(int shotResult, int enemyPosition, int effectiveRadius, int cannonBalls){

    if (abs(shotResult - enemyPosition) < effectiveRadius)
    {
        cout << "Hit!"; 
        
    }
    else if(shotResult > enemyPosition)
    {

        cout << "Your shot was long. ";
    }
    else{

        cout << "Your shot was short. ";

    }

    cout << " Your shot travelled " << shotResult << " feet. You have " << cannonBalls << " left. " << endl;

}



int EngageOthers(int shots){

    int result = 0;     //0 = Don't play again (default), else return 1.
    bool success = false;    

    string response;
   
    
    do {       
            cout << "I see others, would you like to shoot again (Y/N) ";

            if (!(cin >> response)){

                cout << "Please enter Y or N. "; 
                continue;
            }

            if (response == "Y" or response == "y"){
                
                result = 1;
                success = true;

            } else if ( response == "N" or response == "n") {

                result = 0;
                success = true;
            }
            else{
                 cout << "Please enter Y or N. " << endl; 
                 success = false;
            }

            

    } while (!success);

    return result;
}


int RunApp(int shots){    

    bool success    = false;
    bool breakApp   = false;
    bool shotsLeft  = true;
    int effectiveRadius = 50;
    int result = 0;  

    int cannonBalls = shots;
    int enemyPosition = GetEnemyPosition();
    int angleFromUser;
    int shotResult = 0;
    
    do {

        if (cannonBalls == 0){

            cout << "You ran out of cannon balls. " ;
            shotsLeft = false;
            breakApp = true;
            success = false;
            continue;
        }

        else {

            angleFromUser = GetAngleFromUser();     

            //Fire !    
            cannonBalls = cannonBalls - 1;                    
            shotResult = CalculateShot(angleFromUser);     
            success = (DetermineShotSuccess(shotResult,enemyPosition,effectiveRadius));
            DisplayShotResults(shotResult, enemyPosition, effectiveRadius, cannonBalls);

            if (success){

                breakApp = true;

            }
        }

    } while (!breakApp );

    if (success)
    {

        cout << "You hit the enemy" << endl;

        if (cannonBalls > 0 &&  EngageOthers(cannonBalls) == 1)
        {
            
            RunApp(cannonBalls);
            
        }
    }
    else{

        cout << "You missed the enemy. " << endl;

    }   

    return result;
}

int PlayAgain(){

    bool success = false;
    int result = 0;
    string input;
   

    do {

         cout << endl << "Would you like to play again? (Y/N): ";

        if (!(cin >> input)){
            cout << "Please enter Y or N" << endl;
            continue;
        }

        else{

            if (input == "Y" or input == "y")
            {
                result = 1;
                success = true;
            }
            else if (input == "N" or input == "n")
            {
                result = 0;
                success = true;
            }
            else{
                cout << "Please enter Y or N" << endl;
                success = false;
            }
        }


    } while (!success);

    return result;
}

int main(){

    StartUp();

    int shots = 10;
    bool run = true;

    do {

        RunApp(shots);

        int again = PlayAgain();

        if (again != 1)
        {
        
            run = false;

        }

    } while (run);
    
    

    cout << "Thanks for playing!" << endl;

    return 0;
}

