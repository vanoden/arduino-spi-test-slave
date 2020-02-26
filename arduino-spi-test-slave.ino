/******************************************************/
/* arduino-spi-test-slave                             */
/* Test script for new SPI communications libraries.  */
/* A. Caravello - 2/25/2020                           */
/******************************************************/

#include <SPI_Channel.h>
#include <SPI_Request.h>
#include <SPI_Response.h>

SPI_Channel spi;

bool connected = false;
/* Setup UART and SPI Serial */
void setup (void) {
  /* Start up Serial Comms for Debugging */
  Serial.begin(115200);

  connected = spi.connect();
  if (! connected) {
    Serial.println("Error in SPI");
  }
  else {
    Serial.println("Ready to receive");
  }
}  

void loop (void)
{
  if (connected && spi.available()) {
    SPI_Request request = spi.receive();
    SPI_Response response;
    response.content("Ok");
    spi.send(response);
  }
}
