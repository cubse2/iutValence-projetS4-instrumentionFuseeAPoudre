#define S_PIN 8

/* A supprimer
Connect the SCL pin on the breakout to the SCL on a Mega it is also known as digital 21
Connect the SDA pin on the breakout to on a Mega it is also known as digital 20 
Connect the VIN pin on the breakout to 5V 
Connect the GND pin on the breakout to the GND pin on your Uno

MOSI - pin 51, 
MISO - pin 50, 
CLK - pin 52, 
CS - pin 4 (CS pin can be changed) and pin #52 (SS) must be an output
*/

/*Toutes les valeurs sont strictement positif*/
#define SERVO_PIN 9             // pin du servomoteur
#define SPEAKER_PIN 8           // pin du speaker

#define NB_RECORD 5             // nombre d'échantillons pris pour faire une moyenne de 1 à 10, au dela c'est trop lent
/* Plus la valeur de NB_RECORD est eleve plus le nombre de donnees recolter sera reduit mais la precision des valeurs est plus importante
 et inversement. Si la valeur est faible, il y aura bien plus de valeur mais la precision sera faible.*/
#define ROTATION 180            // angle de rotation du servomoteur superieur a 0

#define INITIALIZATION true     // 'true' si on veut effectuer la premiere etape, 'false' sinon
#define TIME_BEFORE_DEPLOY 0    // temps avant le déploiment du parachute (en seconde) de 0 à 25 seconde
#define FALL_DISTANCE 1         // distance de chute minimum après le déploiment du parachute (en metre) superieur a 0
