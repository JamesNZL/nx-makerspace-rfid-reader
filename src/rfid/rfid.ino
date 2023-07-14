/*
 * This is a modified MFRC522 library example; for further details and other examples see: https://github.com/OSSLibraries/Arduino_MFRC522v2
 *
 * Pin layout used:
 * ---------------------------------------
 *             MFRC522      Arduino
 *             Reader/PCD   Uno/101
 * Signal      Pin          Pin
 * ---------------------------------------
 * SPI SS      SDA(SS)      10
 * SPI MOSI    MOSI         11 / ICSP-4
 * SPI MISO    MISO         12 / ICSP-1
 * SPI SCK     SCK          13 / ICSP-3
 */

#include <MFRC522Debug.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522v2.h>

#define SDA_SS_PIN 10

MFRC522DriverPinSimple ss_pin(SDA_SS_PIN);
MFRC522DriverSPI spi_driver { ss_pin };

MFRC522 reader { spi_driver };

void setup()
{
	Serial.begin(115200);
	// Initialise the MFRC522 RFID reader
	reader.PCD_Init();
}

void loop()
{
	if (!reader.PICC_IsNewCardPresent() || !reader.PICC_ReadCardSerial())
	{
		return;
	}

	// Show some details of the PICC (that is: the tag/card).
	Serial.print(F("Card UID:"));
	MFRC522Debug::PrintUID(Serial, reader.uid);
	Serial.println();

	/*
	 TODO: Debounce scanning (or do this on the server), Flash LED, transmit message to server, etc.
	 */

	// Halt PICC, so that the same card is not read multiple times (unless it is removed and re-scanned)
	reader.PICC_HaltA();
	// Stop encryption on PCD.
	reader.PCD_StopCrypto1();
}