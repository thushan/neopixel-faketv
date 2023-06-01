from PIL import Image
import sys

# Output one hex byte with C formatting & line wrap ------------------------

numBytes = 0  # Total bytes to be output in table
byteNum  = 0  # Current byte number (0 to numBytes-1)
cols     = 12 # Current column number in output (force indent on first one)

def writeByte(n):
        global cols, byteNum, numBytes

        cols += 1                      # Increment column #
        if cols >= 12:                 # If max column exceeded...
                print                  # end current line
                sys.stdout.write("  ") # and start new one
                cols = 0               # Reset counter
        sys.stdout.write("{0:#0{1}X}".format(n, 4))
        byteNum += 1
        if byteNum < numBytes:
                sys.stdout.write(",")
                if cols < 11:
                        sys.stdout.write(" ")

# Mainline code ------------------------------------------------------------

# Output 8-bit gamma-correction table:
sys.stdout.write("const uint8_t PROGMEM gamma8[] = {")
numBytes = 256
for i in range(256):
        base     = 1 + (i / 3)  # LCD, CRT contrast is never pure black
        overhead = 255.0 - base
        writeByte(base + int(pow(i / 255.0, 2.7) * overhead + 0.5))
print(" },")


# Output color data (2 bytes per pixel):
sys.stdout.write("colors[] = {")
image        = Image.open("colour-pallete.png")
image.pixels = image.load()
numBytes     = image.size[0] * image.size[1] * 2
byteNum      = 0
cols         = 12
for y in range(image.size[1]):
        for x in range(image.size[0]):
                r = image.pixels[x, y][0]
                g = image.pixels[x, y][1]
                b = image.pixels[x, y][2]
                # Convert 8/8/8 (24-bit) RGB to 5/6/5 (16-bit):
                writeByte((r & 0xF8) | (g >> 5))
                writeByte(((g & 0x1C) << 3) | (b >> 3))
print(" };")