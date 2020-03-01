
// Copyright 2020 Josh Bailey (josh@vandervecken.com)

// Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to us
e, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of t
he Software, and to permit persons to whom the Software is furnished to do so, s
ubject to the following conditions:

// The above copyright notice and this permission notice shall be included in al
l copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM
PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS F
OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR CO
PYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// https://github.com/johnzl-777/DRAMutils
// Missing from DRAMUtils docs:
// DI is pin 9
// DO is pin 10
// TODO: eliminate slow digitalWrite()/digitalRead() from DRAMutils.
#include <DRAMutils.h> 

void setup()
{
  DRAM_setup();
  Serial.begin(115200);
}

void loop()
{
  // TODO: add more tests.
  // Write alternating 0/1s to entire 16b address space.
  for (byte bval = 0; bval < 2; ++bval) {
    for (uint16_t row = 0; row < 256; ++row) {
      for (uint16_t col = 0; col < 256; ++col) {
        mem_addr addr = {.row = row, .col = col};
        DRAM_write(addr, bval);
        byte rbval = DRAM_read(addr);
        // Dump row/col on mismatch.
        if (rbval != bval) {
          Serial.print(addr.row);
          Serial.print(":");
          Serial.print(addr.col);
          Serial.print(" w:");
          Serial.print(bval);
          Serial.print(" r:");
          Serial.println(rbval);
        }
        DRAM_refresh(addr);
      }
    }
  }
  Serial.println("===");
}
