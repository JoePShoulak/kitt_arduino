# Structure

## Up-Front Notes
I got a lot of help from AI and friends on this project. The following is my best understanding of the structure of the project. I apologize for any confusion or inaccuracies. 

## Kitt.ino / Main

`kitt.ino` is the main file, and is responsible for bringing together all the other parts. Because of that, I'm trying to keep it as light as possible, and move all logic and funcionality to other files. 

## Helpers

### Brief

Helpers generally assist with offloading some code out of the `kitt.ino` file to keep it neat and tidy

### Audio Helper

A psuedo-class to store some helpful audio functionality

### Colors

A simple helper file that just stores our colors to be shared between classes. 

### Config

The main data file of the project. It is more responible for implementing the UI, Audio, and Logic than the main file is. This is a bit of a mess of a file, and it could probably be several different files. I'm not entirely sure what to do with this part. 

### Gauge Anim

This is a file that will be removed. It animates the gauges in order to make them fun too look at before they're actually hooked up to things. It will be replaced by the fact that the gauges will be updated with relevant data from sensors.

### lv_conf.h

This is a helper file to configure LVGL, but I haven't totally figured out when and how to use it. I know it's required to get more fonts to work, but I haven't gotten more fonts to work; so I'm stuck with this font and this file, for now. 

### lvgl wrapper
I think the AI created this in order to try to get fonts to work. I think it can be safely removed if the other includes sre updated. 

### UI

A wrapper class for all UI functionality just to keep all the initializations and logic in the same file and seperate from kitt.ino which would already be way too long and busy if we had not broken out as much as we do (even if it might be a bit overboard).

### Voice Synth

The animation that makes the voice visualizer look like it's talking. Like the gauge and the speedometer, eventually I hope for this to be replaced by real data. 

## Higher Components 

### Button Panel

The button panel is a 2x4 grid of buttons made into a tile ready to use by `LVGL`

### Gauge Tile

Because we're using swipable horizontal major UI elements, we're using LVGL's tiles in order to use the best tool for the job. Like Button Panels above, a Gauge Tile is an LVGL tile that consists of a bunch of animated gauges that currently animate randomly, but will represent real data. On one of the gauge tiles, there's also a speedometer. 

### Voice Tile 

The "home screen" tile, this tile has the voice visualizer, all the indicators, and 3 buttons that behave pretty differently from the rest. 

## Components

### Button

The core of this build. Some are square, some are rectangle, but that have a boolean for if they can be toggled, a boolean for if they start activated (if toggleable), and a boolean for if they require a long-press to change the state. Their color by default depends on those properties. Momentary (non-toggleable) buttons are green if "non-severe" and orange if "severe" (which is the name for the parameter that dictates if they take a long press). Toggleable buttons are yellow if non-severe, or red if severe. 

There are validators before and callbacks after each button activation. The validators make sure conditions are met to be able to activate the button. Callbacks dictate what happens after the button is pressed, including handling what audio clip is played. 

### Gauge

A linear gauge that shows a value graphically. They're currently being randomly animated, but will provide data from sensors. 

### Indicator

Basically, a light bulb with a label. These just show certain alerts that have not been defined yet. The only one that is operative is the AUD indicator which shows when audio is playing. If you tap it, it stops the audio, but in general indicators should not be able to be tapped and have an effect. I just did it to the audio indicator in case you start a long clip and want to stop it. It's basically a bebug tool / easter egg that I intend to keep.

### Pop up

This is a class that is definitely used for error messages when trying to press a button that isn't allowed due to the state(s) of other buttons. I believe it's also used when going into EVADE/blackout mode, which turns off the screen. In order to create a mask from other UI events triggering, when the screen is turned off the pop up comes up to block all other UI elements. When it is touched, it closes and turns the screen back on at the same time so you never know it was there. 

### Seven Segment

This is the speedometer, but it could be used generally as something else, I suppose. I have no other plans for it, so it could well be renamed speedometer. Like the gauges, it is currently randomly animated in a drunken walk. 

### Voice Visualizer

The object on the main screen that animates when audio plays. Currently filled with dummy animation, but later to be updated by real sensor data. 
