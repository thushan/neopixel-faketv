# Neopixel Fake TV Simulator

An arduino nano project based on the excellent article from [Adafruit: Fake TV Light for Engineers](https://learn.adafruit.com/fake-tv-light-for-engineers/overview) by Phillip Burgess.

This code is essentially a working version of Phillips code with some extra delicious tweaks.

## Hardware

* Arduino Nano / Mega / Uno
* [NeoPixel from Adafruit](https://www.adafruit.com/category/168) (either a Ring in [24-LED](https://www.adafruit.com/product/1586) or [16-LED](https://www.adafruit.com/product/1463) or a [Stick](https://www.adafruit.com/product/1426))

## Configuration

The two main things you'll need to configure to use this are found in `neopixel-tv.ino`:

```
#define NUM_LEDS 16
#define PIN      12
```

* **NUM_LEDS** signifies the number of LEDs your NeoPixel has. (Eg. 16)
* **PIN** signifies the PIN you've plugged the NeoPixel into. (Eg. D12 = 12)

You'll need to import the NeoPixel library from Arduino IDE or PlatformIO to flash this on your Arduino.

```
Sketch uses 29278 bytes (95%) of program storage space. Maximum is 30720 bytes.
Global variables use 57 bytes (2%) of dynamic memory, leaving 1991 bytes for local variables. Maximum is 2048 bytes.
```

1991 was a great year - it was when [Id Software was born](https://www.giantbomb.com/id-software/3010-347/).