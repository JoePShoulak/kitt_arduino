# KITT Arduino Example

This example demonstrates a simple LVGL UI with button panels for the Arduino GIGA Display. The project now includes a basic audio player which loads an MP3 file from a USB flash drive.

## Preparing a USB drive

1. **Format the drive as FAT32.** Use your operating system's disk tool to format the 32&nbsp;GB drive as FAT32. Other filesystems may not be recognized by the Arduino GIGA.
2. **Copy the audio file.** Place `explode.mp3` in the root directory of the drive.
3. **Eject safely.** Unmount/eject the drive before connecting it to the board.

After these steps the drive can be connected to the USB host port of the Arduino GIGA.
