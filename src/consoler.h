#ifndef _CPP_CONSOLER_CONSOLER_H
#define _CPP_CONSOLER_CONSOLER_H

// ======================================================================

#include <string>

// ----------------------------------------------------------------------

#include "types.h"

// ======================================================================

namespace console {

// ======================================================================

class String {
public:
	String();
	String( std::string str, Properties props = Properties() );

public:
	inline void set_properties( Properties props ) { m_properties = props; }
	inline Properties get_properties() const { return m_properties; }
	inline Properties& get_properties() { return m_properties; }

	inline void set_string( std::string str ) { m_str = str; }
	inline std::string get_string() const { return m_str; }
	inline std::string& get_string() { return m_str; }

	std::string format();

private:
	Properties m_properties;
	std::string m_str;
};

// ----------------------------------------------------------------------

std::string set_string_properties( std::string str, Properties props );

std::string foreground( std::string str, Color_16 col );
std::string foreground( std::string str, uint8_t col );
std::string foreground( std::string str, True_Color col );

std::string background( std::string str, Color_16 col );
std::string background( std::string str, uint8_t col );
std::string background( std::string str, True_Color col );

std::string bold( std::string str );
std::string dim( std::string str );
std::string italic( std::string str );
std::string blink( std::string str );
std::string reverse( std::string str );
std::string hidden( std::string str );
std::string strike( std::string str );
std::string underline( std::string str, Underline_Mode mode );

// ======================================================================

}	 // namespace console

// ======================================================================

#endif
