// ======================================================================

#include <consoler.h>

// ======================================================================

int main( int argc, char* argv[] ) {
	// Defaults
	{
		console::String str{ "Default modes" };
		printf( "%s\n", str.format().c_str() );
	}

	// Color_16
	{
		console::Properties props;
		props.foreground = console::Color_16::RED;
		props.background = console::Color_16::GREEN;

		console::String str{ "foreground: Color_16::RED, background: Color_16::GREEN", props };
		printf( "%s\n", str.format().c_str() );
	}

	// Color_256
	{
		console::Properties props;
		props.foreground = uint8_t( 105u );
		props.background = uint8_t( 205u );

		console::String str{ "foreground: 105, background: 205", props };
		printf( "%s\n", str.format().c_str() );
	}

	// True_Color
	{
		console::Properties props;
		props.foreground = console::True_Color{ 100u, 200u, 50u };
		props.background = console::True_Color{ 50u, 100u, 200u };

		console::String str{ "foreground: {100u, 200u, 50u}, background: {50u, 100u, 200u}",
							 props };
		printf( "%s\n", str.format().c_str() );
	}

	// Modes
	{
		printf( "%s\n", console::bold( "Bold" ).c_str() );
		printf( "%s\n", console::dim( "Dim" ).c_str() );
		printf( "%s\n", console::italic( "Italic" ).c_str() );
		printf( "%s\n", console::blink( "Blink" ).c_str() );
		printf( "%s\n", console::reverse( "Reverse" ).c_str() );
		printf( "%s\n", console::hidden( "Hidden" ).c_str() );
		printf(
			"%s\n",
			console::underline( "Underline", console::Underline_Mode::SINGLE ).c_str() );
		printf( "%s\n",
				console::underline( "Double Underline", console::Underline_Mode::DOUBLE )
					.c_str() );
	}

	// Example
	{
		printf( "This message has an %s, it's %s important that you fix it.\n",
				console::underline( console::bold( console::foreground(
										"ERROR", console::Color_16::RED ) ),
									console::Underline_Mode::SINGLE )
					.c_str(),
				console::italic( "really" ).c_str() );
	}
}

// ======================================================================
