#include "Hardware.h"

Hardware hardware;

Hardware::Hardware() : scanner(Scanner()) {}

void Hardware::init() {}

void Hardware::update() { scanner.update(); }