# ===== CONFIGURATION =====
SKETCH_NAME := kitt.ino
BOARD := arduino:mbed_giga:giga
PORT := COM3
BAUD := 115200
BUILD_DIR := build

# ===== COMMANDS =====
all: compile upload monitor

compile:
	@echo ">>> Compiling..."
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD_DIR) $(SKETCH_NAME)

upload:
	@echo ">>> Uploading..."
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) --input-dir $(BUILD_DIR)

clean:
	@echo ">>> Cleaning build directory..."
	rm -rf $(BUILD_DIR)

convert:
	@echo ">>> Running MP3-to-WAV conversion script..."
	@scripts/convert.sh

monitor:
	@echo ">>> Opening Serial Monitor..."
	arduino-cli monitor -p $(PORT) --config $(BAUD)
