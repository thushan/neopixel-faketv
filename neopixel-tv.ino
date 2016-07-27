#include <Adafruit_NeoPixel.h>
#include "data.h"

#define NUM_LEDS 16
#define PIN      12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB);

uint32_t pixelNum;
uint16_t pr = 0, pg = 0, pb = 0; // Prev R, G, B

void setup() {
  strip.begin();
  randomSeed(analogRead(A0));
  pixelNum = random(numPixels); // Begin at random point
}

void loop() {
  uint32_t totalTime, fadeTime, holdTime, startTime, elapsed;
  uint16_t nr, ng, nb, r, g, b, i;
  uint8_t  hi, lo, r8, g8, b8, frac;

  if (counter20ms >= holdTime) {
    difference = abs(endpixel - startpixel);

    if (elapsed >= fadeTime) {
      // Read next 16-bit (5/6/5) color
      hi = pgm_read_byte(&colors[pixelNum * 2]);
      lo = pgm_read_byte(&colors[pixelNum * 2 + 1]);

      if (++pixelNum >= numPixels) { pixelNum = 0; }

      // Expand to 24-bit (8/8/8)
      r8 = (hi & 0xF8) | (hi >> 5);
      g8 = (hi << 5) | ((lo & 0xE0) >> 3) | ((hi & 0x06) >> 1);
      b8 = (lo << 3) | ((lo & 0x1F) >> 2);

      // Apply gamma correction, further expand to 16/16/16
      nr = (uint8_t)pgm_read_byte(&gamma8[r8]) * 257; // New R/G/B
      ng = (uint8_t)pgm_read_byte(&gamma8[g8]) * 257;
      nb = (uint8_t)pgm_read_byte(&gamma8[b8]) * 257;

      totalTime = HwRandom(12, 125);                          // Semi-random pixel-to-pixel time
      fadeTime  = HwRandom(0, totalTime);                 // Pixel-to-pixel transition time

      if (HwRandom(10) < 3) { fadeTime = 0; }                 // Force scene cut 30% of time

      holdTime  = counter20ms + totalTime - fadeTime; // Non-transition time
      startTime = counter20ms;
    }

    elapsed = counter20ms - startTime;

    if (fadeTime) {
      r = map(elapsed, 0, fadeTime, pr, nr); // 16-bit interp
      g = map(elapsed, 0, fadeTime, pg, ng);
      b = map(elapsed, 0, fadeTime, pb, nb);
    } else {                                                     // Avoid divide-by-fraczero in map()
      r = nr;
      g = ng;
      b = nb;
    }

    for (i = 0; i < difference; i++) {
      
      r8   = r >> 8;                 // Quantize to 8-bit
      g8   = g >> 8;
      b8   = b >> 8;

      frac = (i << 16) / difference; // LED index scaled to 0-65535 (16Bit)

      if ((r8 < 255) && ((r & 0xFF) >= frac)) { r8++; } // Boost some fraction
      if ((g8 < 255) && ((g & 0xFF) >= frac)) { g8++; } // of LEDs to handle
      if ((b8 < 255) && ((b & 0xFF) >= frac)) { b8++; } // interp > 8bit

      strip.setPixelColor(i + startpixel, r8, g8, b8);
    }

    pr = nr; // Prev RGB = new RGB
    pg = ng;
    pb = nb;
  }
}