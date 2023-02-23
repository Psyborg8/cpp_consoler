// ======================================================================

#include "consoler.h"

// ======================================================================

#include <fmt/format.h>
#include <vector>

// ======================================================================

namespace console {

// ======================================================================

String::String() : m_properties(), m_str() {}

// ----------------------------------------------------------------------

String::String( std::string str, Properties props ) :
	m_properties( props ), m_str( str ) {}

// ----------------------------------------------------------------------

std::string String::format() {
	return set_string_properties( m_str, m_properties );
}

// ======================================================================

std::string set_string_properties( std::string str, Properties props ) {
	// Modes
	std::vector< uint8_t > modes;
	modes.reserve( 16u );

	// Foreground Color
	if( std::holds_alternative< Color_16 >( props.foreground ) ) {
		modes.push_back( static_cast< uint8_t >( std::get< Color_16 >( props.foreground ) ) );
	}
	else if( std::holds_alternative< uint8_t >( props.foreground ) ) {
		modes.push_back( 38u );
		modes.push_back( 5u );
		modes.push_back( std::get< uint8_t >( props.foreground ) );
	}
	else if( std::holds_alternative< True_Color >( props.foreground ) ) {
		True_Color col = std::get< True_Color >( props.foreground );

		modes.push_back( 38u );
		modes.push_back( 2u );
		modes.push_back( col.r );
		modes.push_back( col.g );
		modes.push_back( col.b );
	}

	// Background Color
	if( std::holds_alternative< Color_16 >( props.background ) ) {
		modes.push_back(
			static_cast< uint8_t >( std::get< Color_16 >( props.background ) ) + 10u );
	}
	else if( std::holds_alternative< uint8_t >( props.background ) ) {
		modes.push_back( 48u );
		modes.push_back( 5u );
		modes.push_back( std::get< uint8_t >( props.background ) );
	}
	else if( std::holds_alternative< True_Color >( props.background ) ) {
		True_Color col = std::get< True_Color >( props.background );

		modes.push_back( 48u );
		modes.push_back( 2u );
		modes.push_back( col.r );
		modes.push_back( col.g );
		modes.push_back( col.b );
	}

	// Bold
	if( props.bold )
		modes.push_back( static_cast< uint8_t >( Mode::BOLD ) );

	// Dim
	if( props.dim )
		modes.push_back( static_cast< uint8_t >( Mode::DIM ) );

	// Italic
	if( props.italic )
		modes.push_back( static_cast< uint8_t >( Mode::ITALIC ) );

	// Blink
	if( props.blink )
		modes.push_back( static_cast< uint8_t >( Mode::BLINK ) );

	// Reverse
	if( props.reverse )
		modes.push_back( static_cast< uint8_t >( Mode::REVERSE ) );

	// Hidden
	if( props.hidden )
		modes.push_back( static_cast< uint8_t >( Mode::HIDDEN ) );

	// Strike
	if( props.strike )
		modes.push_back( static_cast< uint8_t >( Mode::STRIKE ) );

	// Underline
	if( props.underline == Underline_Mode::SINGLE )
		modes.push_back( static_cast< uint8_t >( Mode::UNDERLINE ) );
	else if( props.underline == Underline_Mode::DOUBLE )
		modes.push_back( static_cast< uint8_t >( Mode::DOUBLE_UNDERLINE ) );


	// Construct string
	std::string modes_str;
	for( size_t i = 0; i < modes.size(); ++i ) {
		modes_str += std::to_string( modes.at( i ) );

		if( i < modes.size() - 1u )
			modes_str += ";";
	}

	return fmt::format( "\033[{}m{}\033[0m", modes_str, str );
}

// ----------------------------------------------------------------------

std::string foreground( std::string str, Color_16 col ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( col ),
						str,
						static_cast< uint8_t >( Color_16::DEFAULT ) );
}

// ----------------------------------------------------------------------

std::string foreground( std::string str, uint8_t col ) {
	return fmt::format(
		"\033[38;5;{}m{}\033[{}m", col, str, static_cast< uint8_t >( Color_16::DEFAULT ) );
}

// ----------------------------------------------------------------------

std::string foreground( std::string str, True_Color col ) {
	return fmt::format( "\033[38;2;{};{};{}m{}\033[38{}m",
						col.r,
						col.g,
						col.b,
						str,
						static_cast< uint8_t >( Color_16::DEFAULT ) );
}

// ----------------------------------------------------------------------

std::string background( std::string str, Color_16 col ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( col ) + 10u,
						str,
						static_cast< uint8_t >( Color_16::DEFAULT ) + 10u );
}

// ----------------------------------------------------------------------

std::string background( std::string str, uint8_t col ) {
	return fmt::format(
		"\033[48;5;{}m{}\033[{}m", col, str, static_cast< uint8_t >( Color_16::DEFAULT ) + 10u );
}

// ----------------------------------------------------------------------

std::string background( std::string str, True_Color col ) {
	return fmt::format( "\033[48m;2;{};{};{}m{}\033[{}m",
						col.r,
						col.g,
						col.b,
						str,
						static_cast< uint8_t >( Color_16::DEFAULT ) + 10u );
}

// ----------------------------------------------------------------------

std::string bold( std::string str ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( Mode::BOLD ),
						str,
						static_cast< uint8_t >( Mode::RESET_BOLD ) );
}

// ----------------------------------------------------------------------

std::string dim( std::string str ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( Mode::DIM ),
						str,
						static_cast< uint8_t >( Mode::RESET_DIM ) );
}

// ----------------------------------------------------------------------

std::string italic( std::string str ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( Mode::ITALIC ),
						str,
						static_cast< uint8_t >( Mode::RESET_ITALIC ) );
}

// ----------------------------------------------------------------------

std::string blink( std::string str ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( Mode::BLINK ),
						str,
						static_cast< uint8_t >( Mode::RESET_BLINK ) );
}

// ----------------------------------------------------------------------

std::string reverse( std::string str ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( Mode::REVERSE ),
						str,
						static_cast< uint8_t >( Mode::RESET_REVERSE ) );
}

// ----------------------------------------------------------------------

std::string hidden( std::string str ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( Mode::HIDDEN ),
						str,
						static_cast< uint8_t >( Mode::RESET_HIDDEN ) );
}

// ----------------------------------------------------------------------

std::string strike( std::string str ) {
	return fmt::format( "\033[{}m{}\033[{}m",
						static_cast< uint8_t >( Mode::STRIKE ),
						str,
						static_cast< uint8_t >( Mode::RESET_STRIKE ) );
}

// ----------------------------------------------------------------------

std::string underline( std::string str, Underline_Mode mode ) {
	if( mode == Underline_Mode::SINGLE )
		return fmt::format( "\033[{}m{}\033[{}m",
							static_cast< uint8_t >( Mode::UNDERLINE ),
							str,
							static_cast< uint8_t >( Mode::RESET_UNDERLINE ) );
	else if( mode == Underline_Mode::DOUBLE )
		return fmt::format( "\033[{}m{}\033[{}m",
							static_cast< uint8_t >( Mode::DOUBLE_UNDERLINE ),
							str,
							static_cast< uint8_t >( Mode::RESET_UNDERLINE ) );

	return str;
}

// ======================================================================

}	 // namespace console

// ======================================================================
