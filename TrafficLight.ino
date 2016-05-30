/*
* Three light test.
* May 20, 2016.
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//LED declaration
const int RL1 = 13,
          YL1 = 12,
          GL1 = 11;

const int RL3 = 10,
          YL3 = 9,
          GL3 = 8;

const int PL1 = 7;

//Time variable declaration
unsigned long cM;
              
const int rI = 5000,
          yI = 1000;

const long mC = 1,
           pM = 0;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
*  This method turns on the red LED while simultaneously turning off the yellow LED since these operations are immediately consecutive to eachother. 
*/
void onR (int y, int r){
  digitalWrite (y, LOW);
  digitalWrite (r, HIGH);
}

/*
*  This method turns on the yellow LED while simultaneously turning off the green LED since these operations are immediately consecutive to eachother. 
*/
void onY(int g, int y){
  digitalWrite (g, LOW);
  digitalWrite (y, HIGH);
}

/*
*  This method turns on the green LED while simultaneously turning off the red LED since these operations are immediately consecutive to eachother. 
*/
void onG(int r, int g){
  digitalWrite (r, LOW);
  digitalWrite (g, HIGH);
  
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
*  This method initializes all compoenents of the circuit.
*/
void setup(){
  pinMode (RL1, OUTPUT);
  pinMode (YL1, OUTPUT);
  pinMode (GL1, OUTPUT);
  
  pinMode (RL3, OUTPUT);
  pinMode (YL3, OUTPUT);
  pinMode (GL3, OUTPUT);
  
  pinMode (PL1, OUTPUT); 
  Serial.begin (9600);
}

/*
*  This method is the active loop of the system.
*/
void loop (){
  cM = millis();  

  if (cM >= 1000 * mC){
    pM++;
    mC++;
  }
  
  if(pM  > 11){
      pM = 0;
  }
  
  if (pM >= 0 && pM < 6){
    if (pM < 5){
      onG(RL1, GL1);
    }
    
    if(pM == 5){
      onY (GL1, YL1);
    }
    onR (YL3, RL3);
  }

  if(pM >= 6 && pM < 12){
    onR(YL1, RL1);
    if (pM < 11){
      onG (RL3, GL3);
    }
    if(pM == 11){
      onY(GL3, YL3);  
   }
    
 }
  

