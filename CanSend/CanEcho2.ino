#include <SPI.h>
#include <mcp2515/mcp2515.h>

struct can_frame sendFrame;
struct can_frame recvFrame;

MCP2515 mcp2515(10); /* CS = 10 */

void setup()
{
	sendFrame.can_id = 0x222; /* Packet identifier */
	sendFrame.can_dlc = 8; /* Payload length */
	sendFrame.data[0] = 0x61;
	sendFrame.data[1] = 0x62;
	sendFrame.data[2] = 0x63;
	sendFrame.data[3] = 0x64;
	sendFrame.data[4] = 0x65;
	sendFrame.data[5] = 0x66;
	sendFrame.data[6] = 0x67;
	sendFrame.data[7] = 0x68;

	while (!Serial)
		;
	Serial.begin(115200);
	SPI.begin();

	if (mcp2515.reset() != MCP2515::ERROR_OK)
		Serial.println("Error reset!");
	if (mcp2515.setBitrate(CAN_1000KBPS, MCP_16MHZ) != MCP2515::ERROR_OK)
		Serial.println("Error bitrate");
	if (mcp2515.setNormalMode() != MCP2515::ERROR_OK)
		Serial.println("Err setting mode!");

	// Serial.println("Example: Write to CAN");
}

int i = 0;
MCP2515::ERROR result;

void loop()
{
	/* If a packet needs to be send */
	if (Serial.available() > 0)
	{
		Serial.read();

		result = mcp2515.sendMessage(&sendFrame);
		if (result == MCP2515::ERROR_OK)
		{
			Serial.print(i++);
			Serial.print(". SEND: ");
			Serial.print(sendFrame.can_id, HEX); // print ID
			Serial.print(" # ");
			Serial.print(sendFrame.can_dlc, HEX); // print DLC
			Serial.print(" # ");
			for (int i = 0; i < sendFrame.can_dlc; i++)
			{
				Serial.print(sendFrame.data[i], HEX);
				Serial.print(" ");
			}
			Serial.print("\n");
		}
		else
		{
			Serial.print(i++);
			Serial.print(". Failed to send frame: ");
			Serial.print(result);
			Serial.print("\n");
		}
	}

	/* Check for incoming packets */
	if (mcp2515.checkReceive())
	{
		result = mcp2515.readMessage(&recvFrame);
		if (result == MCP2515::ERROR_OK)
		{
			Serial.print(i++);
			Serial.print(". RECV: ");
			Serial.print(recvFrame.can_id, HEX); // print ID
			Serial.print(" # ");
			Serial.print(recvFrame.can_dlc, HEX); // print DLC
			Serial.print(" # ");
			for (int i = 0; i < recvFrame.can_dlc; i++)
			{
				Serial.print(recvFrame.data[i], HEX);
				Serial.print(" ");
			}
			Serial.print("\n");
		}
		else
		{
			Serial.print("Failed to read frame: ");
			Serial.print(result);
			Serial.print("\n");
		}
	}
}
