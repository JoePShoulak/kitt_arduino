#!/bin/bash

# Set to Windows ffmpeg.exe path
FFMPEG="/c/Users/joeps/Desktop/ffmpeg.exe"

if [ $# -ne 1 ]; then
    echo "Usage: $0 input.mp3"
    exit 1
fi

INPUT="$1"
OUTPUT="./${INPUT%.*}.wav"

echo "Converting $INPUT → $OUTPUT"
"$FFMPEG" -i "$INPUT" -ar 44100 -ac 1 -sample_fmt s16 "$OUTPUT"

echo "Done!"
