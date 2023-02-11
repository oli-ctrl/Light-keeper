#include <string>

// yoinked from the sprite sheet

static const std::string light = "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";

