# ===== CONFIGURATION =====
SKETCH_NAME := kitt.ino
BOARD := arduino:mbed_giga:giga
PORT := COM7
BAUD := 115200
BUILD_DIR := build

# ===== COMMANDS =====
all: compile upload monitor

install: 
	@echo ">>> Installing..."
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

compile:
	@echo ">>> Compiling..."
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD_DIR) $(SKETCH_NAME)

upload:
	@echo ">>> Uploading..."
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) --input-dir $(BUILD_DIR)

clean:
	@echo ">>> Cleaning build directory..."
	rm -rf $(BUILD_DIR)

monitor:
	@echo ">>> Opening Serial Monitor..."
	arduino-cli monitor -p $(PORT) --config $(BAUD)

loc:
	@echo ">>> Counting lines of code..."
	@files=$$(find . -type f \( -name "*.h" -o -name "*.cpp" \)); \
	count=$$(echo "$$files" | wc -l); \
	lines=$$(cat $$files | wc -l); \
	echo "$$lines lines across $$count files"

# Project specific
convert:
	@echo ">>> Running MP3-to-WAV conversion script..."
	@scripts/convert.sh
	