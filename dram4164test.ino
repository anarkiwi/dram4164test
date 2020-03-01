// Copyright 2020 Josh Bailey (josh@vandervecken.com)q

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// Requires: https://github.com/anarkiwi/DRAMutils
// Missing from DRAMUtils docs:
// DI is pin 9
// DO is pin 10
// TODO: eliminate slow digitalWrite()/digitalRead() from DRAMutils.
#include <DRAMutils.h> 

void setup() {
  DRAM_setup();
  Serial.begin(115200);
}

void loop()  {
  // TODO: add more tests.
  // Write alternating 0/1s to entire 16b address space.
  Serial.println("===");
  mem_addr addr = {.row = 0, .col = 0};
  for (byte bval = 0; bval < 2; ++bval) {
    for (uint16_t row = 0; row < 256; ++row) {
      addr.row = row;
      uint8_t row_mismatches = 0;
      DRAM_refresh(addr);
      for (uint16_t col = 0; col < 256; ++col) {
        addr.col = col;
        DRAM_write(addr, bval);
        volatile byte rbval = DRAM_read(addr);
        // Dump row/col on mismatch.
        if (rbval != bval) {
          if (!row_mismatches++) {
            Serial.print("bit wrong ");
            Serial.print(rbval);
            Serial.print(" r");
            Serial.print(addr.row);
          }
          Serial.print(" c");
          Serial.print(addr.col);
        }
      }
      if (row_mismatches) {
        Serial.println();
      }
    }
    Serial.println();
  }
}
