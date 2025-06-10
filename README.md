# KITT Dashboard Demo for Arduino GIGA

This project recreates a portion of the dashboard from **Knight Rider's** KITT on an [Arduino GIGA R1](https://docs.arduino.cc/hardware/giga-r1/) paired with the official touchscreen display.
It is currently used to experiment with a fun control panel for an augmented golf cart.

## Features

* Designed for the Arduino GIGA R1 with the GIGA Display Shield.
* Swipable interface with three tiles:
  * **Left panel** – button grid in the KITT style.
  * **Center panel** – voice synthesiser display with indicators (default view).
  * **Right panel** – secondary button grid for practical controls.
* Basic audio playback support from USB (see `audio_helper.*`).

The `ref` directory contains screenshots used for layout reference.

## Required Libraries

Install the following libraries using the Arduino Library Manager before compiling:

* `Arduino_GigaDisplay_GFX`
* `Arduino_GigaDisplayTouch`
* `LVGL`
* `GigaAudio` (for audio playback)

These provide support for the display, the capacitive touch interface, the graphics widgets and the audio helper respectively.

## Board Setup

Use the **Arduino GIGA R1** board package. The sketches assume the official GIGA Display Shield is attached.
Ensure the board package and all libraries are up to date in the Arduino IDE or through `arduino-cli`.

## Building and Uploading

1. Open `kitt.ino` in the Arduino IDE.
2. Select **GIGA R1** as the target board and choose the appropriate port.
3. Verify that the libraries listed above are installed.
4. Compile and upload the sketch.

After uploading, the device starts on the center voice tile. Swipe left or right to access the button panels.

Audio files (`*.wav`) are stored in the `data` folder for reference. They can be copied to a USB drive connected to the board if you wish to enable the audio helper. If no USB storage is detected at runtime the sketch simply runs without audio.

## License

This project is released without a specific license. Use at your own risk.

