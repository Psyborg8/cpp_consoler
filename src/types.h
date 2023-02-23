// ======================================================================

#include <cstdint>
#include <variant>

// ======================================================================

namespace console {

// ======================================================================

enum class Color_16 : uint8_t {
	BLACK	= 30,
	RED		= 31,
	GREEN	= 32,
	YELLOW	= 33,
	BLUE	= 34,
	MAGENTA = 35,
	CYAN	= 36,
	WHITE	= 37,

	BRIGHT_BLACK   = 90,
	BRIGHT_RED	   = 91,
	BRIGHT_GREEN   = 92,
	BRIGHT_YELLOW  = 93,
	BRIGHT_BLUE	   = 94,
	BRIGHT_MAGENTA = 95,
	BRIGHT_CYAN	   = 96,
	BRIGHT_WHITE   = 97,

	DEFAULT = 39,
};

// ----------------------------------------------------------------------

struct True_Color {
	uint8_t r{ 255u };
	uint8_t g{ 255u };
	uint8_t b{ 255u };
};

// ----------------------------------------------------------------------

typedef std::variant< Color_16, uint8_t, True_Color > Color_Type;

// ======================================================================

enum class Mode : uint8_t {
	RESET = 0,

	BOLD			 = 1,
	DIM				 = 2,
	ITALIC			 = 3,
	UNDERLINE		 = 4,
	DOUBLE_UNDERLINE = 21,
	BLINK			 = 5,
	REVERSE			 = 7,
	HIDDEN			 = 8,
	STRIKE			 = 9,

	RESET_BOLD		= 22,
	RESET_DIM		= 22,
	RESET_ITALIC	= 23,
	RESET_UNDERLINE = 24,
	RESET_BLINK		= 25,
	RESET_REVERSE	= 27,
	RESET_HIDDEN	= 28,
	RESET_STRIKE	= 29,
};

// ----------------------------------------------------------------------

enum class Underline_Mode : uint8_t {
	NONE,
	SINGLE,
	DOUBLE,
};

// ======================================================================

struct Properties {
	Color_Type foreground{ Color_16::DEFAULT };
	Color_Type background{ Color_16::DEFAULT };

	bool bold{ false };
	bool dim{ false };
	bool italic{ false };
	bool blink{ false };
	bool reverse{ false };
	bool hidden{ false };
	bool strike{ false };
	Underline_Mode underline{ Underline_Mode::NONE };
};

// ======================================================================

}	 // namespace console

// ======================================================================
