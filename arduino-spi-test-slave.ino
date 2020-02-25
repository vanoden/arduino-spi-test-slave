/*************************************************************
 SPI_Hello_Raspi
   Configures an ATMEGA as an SPI slave and demonstrates
   bidirectional communication with an Raspberry Pi SPI master
   by repeatedly sending the text "Hello Raspi"
****************************************************************/


/***************************************************************
 Global Variables
  -hello[] is an array to hold the data to be transmitted
  -marker is used as a pointer in traversing data arrays
/***************************************************************/

unsigned char hello[] = {'H','e','l','l','o',' ',
                         'R','a','s','p','i','\n'};
byte marker = 0;
 

/***************************************************************  
 Setup SPI in slave mode (1) define MISO pin as output (2) set
 enable bit of the SPI configuration register
****************************************************************/
                   
void setup (void)
{
  Serial.begin(115200);
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  Serial.println("Ready to receive");
}  

/***************************************************************  
 Loop until the SPI End of Transmission Flag (SPIF) is set
 indicating a byte has been received.  When a byte is
 received, load the next byte in the Hello[] array into SPDR
 to be transmitted to the Raspberry Pi, and increment the marker.
 If the end of the Hell0[] array has been reached, reset
 marker to 0.
****************************************************************/
bool status = false;
int came = 0;
byte terminator = 0x04;
byte _null = 0x00;
String request;
int startMillis = 0;

void loop (void)
{
  if((SPSR & (1 << SPIF)) != 0)
  {
    came ++;
    if (! status) {
      Serial.println("Incoming");
      status = true;
      startMillis = millis;
    }
    char letter = SPDR;

    if (letter == '\0') {
      Serial.print(".");
    }
    else if (letter == terminator) {
      Serial.println("");
      Serial.print("Received ");
      Serial.print(came);
      Serial.print(" characters: '");
      Serial.print(request);
      Serial.println("'");
      request = "";
      delay(50);
      Serial.println("Responding");
      int marker = 0;
      while (marker < sizeof(hello)) {
        if ((SPSR & (1 << SPIF)) != 0) {
          SPDR = hello[marker];
          marker ++;
          /*delay(10);*/
        }
      }
      Serial.print("Sent ");
      Serial.print(marker);
      Serial.println(" characters");
      SPDR = 4;
      /*delay(50);*/
      status = false;
      came = 0;
    }
    else {
      request += letter;
    }
  }
  if (status && millis > startMillis + 1000) {
    Serial.println("Timed out");
    status = false;
    request = "";
  }
}
