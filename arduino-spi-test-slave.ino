/******************************************************/
/* arduino-spi-test-slave                             */
/* Test script for new SPI communications libraries.  */
/* A. Caravello - 2/25/2020                           */
/******************************************************/

#include <SPI_Channel.h>
#include <SPI_Message.h>

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
    SPI_Message spi_response;
    Serial.println("Incoming Request");
    SPI_Message spi_request = spi.receive();
    if (spi_request.error().length() > 0) {
      Serial.print("Error receiving message: ");
      Serial.println(spi_request.error());
      delay(100);
    }
    if (spi_request.length() > 0) {
      String request = spi_request.content();
      Serial.print("Request: ");
      Serial.println(request);

      //if (request.startsWith("ver")) {
      //  spi_response.content("0.01");
      //}
      //else {
      //  Serial.println("Invalid request");
      //  spi_response.content("Nope");
      //}
      //delay(100);
      //Serial.println("Sending response");
      //if (spi.send(spi_response)) {
      //  Serial.println("Response delivered");
      //}
      //else {
      //  Serial.println(spi.error());
      //}
    }
  }
}
