# Makefile at root of pico-new

PROJECT ?= main_project
BUILD_DIR := build
TTY ?= /dev/ttyACM0
BAUD ?= 115200

.PHONY: all init compile compile-clean flash terminal clean help

# Default target
all: help

# Show help message
help:
	@echo "🛠️  Available commands:"
	@echo "  make init name=<project_name>   - Initialize a new project from the template"
	@echo "  make compile                    - Compile the current project"
	@echo "  make compile-clean              - Clean and recompile the project"
	@echo "  make flash                      - Flash the compiled UF2 to the Pico"
	@echo "  make terminal                   - Open USB serial terminal via picocom"
	@echo "  make clean                      - Delete the build directory"
	@echo "  make help                       - Show this help message"

# Initialize a new project from the template
init:
	@if [ -z "$(name)" ]; then \
		echo "❌ Usage: make init name=<project_name>"; \
		exit 1; \
	fi
	@./init.sh "$(name)"

# Compile the selected project
compile:
	./compile.sh

# Compile with clean build
compile-clean:
	./compile.sh --clean

# Flash using the flash script
flash:
	./flash.sh

# Open serial terminal
terminal:
	picocom -b $(BAUD) $(TTY)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
