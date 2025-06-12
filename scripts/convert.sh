#!/bin/bash

# Convert all mp3 files in the ref directory to wavs in the data directory.
# After a successful conversion the mp3 file is removed from ref.

set -e

# Path to ffmpeg; adjust if necessary
FFMPEG="ffmpeg"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REF_DIR="${SCRIPT_DIR}/../ref"
DATA_DIR="${SCRIPT_DIR}/../data"

shopt -s nullglob
mp3_files=("${REF_DIR}"/*.mp3)

if [ ${#mp3_files[@]} -eq 0 ]; then
    echo "No mp3 files found in ${REF_DIR}"
    exit 0
fi

for mp3 in "${mp3_files[@]}"; do
    base="$(basename "${mp3}" .mp3)"
    wav="${DATA_DIR}/${base}.wav"
    echo "Converting ${mp3} -> ${wav}"
    if "$FFMPEG" -y -i "$mp3" -ar 44100 -ac 2 -sample_fmt s16 "$wav"; then
        rm -f "$mp3"
        echo "Converted and removed ${mp3}"
    else
        echo "Failed to convert ${mp3}" >&2
    fi
done
