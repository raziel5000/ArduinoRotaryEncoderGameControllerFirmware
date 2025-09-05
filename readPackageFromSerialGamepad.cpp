// This is just an extract from the GameStateManager class. The code below is a function which grab an incoming packet and unravel its content. 

void GameStateManager::readPackageFromSerialGamepad()
{
	while (serial.available() >= 6) {
		if (serial.readByte() == 0xAA) {
			uint8_t payload[5];
			int numRead = serial.readBytes(payload, 5);  // LSB, MSB, btn1, btn2, checksum

			uint8_t lsb = payload[0];
			uint8_t msb = payload[1];
			uint8_t button1 = payload[2];  // Pulsante esterno
			uint8_t button2 = payload[3];  // Taster encoder
			uint8_t checksum = payload[4];

			uint8_t computedChecksum = (lsb + msb + button1 + button2) & 0xFF;

			if (checksum == computedChecksum) {
				serialEncoderValue = lsb | (msb << 8);
				serialButtonState = (int)button1;
				serialRotaryButtonState = (int)button2;
				
				if (serialRotaryButtonState == 0)
					canTriggerRotaryButtonState = true;
				
				ofLog() << "Encoder: " << serialEncoderValue
					<< " | ButtonExt: " << serialButtonState
					<< " | Taster: " << serialRotaryButtonState;
			}
			else {
				ofLogWarning() << "Checksum mismatch!";
			}
		}
	}
}
