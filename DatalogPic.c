const char CS_PIN = 1;
const char LD_PIN = 2;

unsigned int value;

void InitSPI() {
 ADPCFG = 0xFFFF; // Set AN pins as digital

 Spi1_Init(); // Initialize SPI module

 TRISC.CS_PIN = 0; // Set CS pin as output
 TRISC.LD_PIN = 0; // Set LD pin as output
}//~


// DAC increments (0..4095) --> output voltage (0..Vref)
void DAC_Output(unsigned int valueDAC) {
 char temp;

 PORTC.CS_PIN = 0; // Select DAC module
 PORTC.LD_PIN = 0; // Enable data transfer

 // Send 2 bytes of valueDAC variable
 temp = (valueDAC >> 8) & 0x0F; // Prepare hi-byte for transfer
 // It's a 12-bit number, so only
 // lower nibble of high byte is used
 temp |= 0x30; // Set MCP4921 control bits
 Spi_Write(temp); // Send data via SPI

 temp = valueDAC; // Prepare lo-byte for transfer
 Spi_Write(temp); // Send data via SPI

 PORTC.LD_PIN = 1; // Disable data transfer
 PORTC.CS_PIN = 1; // Deselect DAC module
}//~


void main() {
 InitSPI();

 value = 2047; // When program starts, DAC gives
 // the output in the mid-range

 while (1) { // Main loop
 DAC_Output(value++);
 if (value > 4095)
 value = 0;
 Delay_ms(5);
 }
}//~!
