import monkey_map;

import <gtest/gtest.h>;

int main( int argc, char* argv[ ] )
{
	testing::InitGoogleTest( &argc, argv );
	if( RUN_ALL_TESTS( ) )
		return 1;
	return static_cast< int >( monkey_map::Result( ).Execute( argc, argv ) );
}
