# Electronic Dice

An Arduino-based electronic dice that generates a random number from 1–6 when a touch sensor is activated. The result is displayed on a 7-segment display and an I2C LCD module.

## Demo
*(Add your video link here)*

## Features
- Touch sensor input to trigger a dice roll
- Suspense animation on the 7-segment display before revealing the result
- Result displayed on both the 7-segment display and a 16x2 I2C LCD
- Current and Previous Result tracked and displayed on the LCD
- Idle animation when waiting for input
- Serial monitor logging for debugging

## Components
- Arduino Uno
- 7-segment display (single digit)
- Touch sensor
- 16x2 I2C LCD module
- Resistors
- Jumper wires
- Breadboard

## Wiring
| Component | Arduino Pin |
|-----------|-------------|
| Segment A | 11 |
| Segment B | 10 |
| Segment C | 9 |
| Segment D | 8 |
| Segment E | 7 |
| Segment F | 6 |
| Segment G | 5 |
| Touch Sensor | 3 |
| I2C LCD SDA | A4 |
| I2C LCD SCL | A5 |

## Libraries Required
- `Wire.h` (built into Arduino IDE)
- `hd44780` — install via Arduino Library Manager

## How It Works
1. On startup the display runs an idle animation and the LCD prompts you to touch the sensor
2. When the sensor is touched, a suspense animation plays on the 7-segment display
3. A random number from 1–6 is generated and shown on both displays
4. After 10 seconds of inactivity, the system returns to idle
