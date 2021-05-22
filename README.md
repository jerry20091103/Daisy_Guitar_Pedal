# Daisy Guitar Pedal
A digital guitar multi-effect pedal project made with Daisy seed and Arduino.  
This is a hybird pedal, using Daisy Seed as DSP processor and a analog module for better overdrive and distortion tone.

## Signal Path
The guitar signal path:
>Guitar Output -> Input Buffer -> Input 0 of Daisy -> Daisy  
>(-> Output 1 of Daisy -> Analog Module -> Input 1 of Daisy -> Daisy) //optional  
>-> Output 0 of Daisy -> Final Ouptut  

The Analog Module contains overdrive, distortion, and a tube boost.

## Features
<ul>
  <li>A 128*64 Monochrome LCD and a 8*8 LED matrix for display.</li>
  <li>10 presets controlled by two footswitchs. (up and down)</li>
  <li>Each preset has 10 "effect slots", the user can insert any effects they like and arrange them in any order.</li>
  <li>Easy UI navigation with four arrow keys and an enter button.</li>
  <li>IR based guitar amp simulation.</li>
  <li>On/Off of each analog modules can be controled digitally by relays.</li>
  <li>All presets and options are stored in an external EEPROM chip.</li>
  <li>All control inputs are handled by interrupts.</li>
</ul>

## Controls
4 foot switches, 5 pushbuttons, and a rotary encoder.  
5 pushbuttons are for up / down / left / right / enter.

## List of effects
<ul>
  <li>Reverb</li>
  <li>Pitchshifter</li>
  <li>Analog Module</li>
  <li>Overdrive (digital)</li>
  <li>Fuzz (digital)</li>
  <li>Compressor</li>
  <li>Gain</li>
  <li>Delay</li>
  <li>Chorus</li>
  <li>Flanger</li>
</ul>

## Dependencies
<ul>
  <li>My fork of <a href=https://github.com/jerry20091103/DaisyDuino>DaisyDuino</a></li>
  <li><a href=https://github.com/evert-arias/EasyButton>EasyButton</a></li>
  <li><a href=https://github.com/mathertel/RotaryEncoder>RotaryEncoder</a></li>
  <li><a href=https://github.com/olikraus/u8g2>u8g2</a></li>
  <li><a href=https://github.com/JChristensen/extEEPROM>extEEPROM</a></li>
  <li><a href=https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library>Adafruit MCP23017 Arduino Library</a></li>
</ul>
