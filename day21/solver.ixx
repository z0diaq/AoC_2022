export module monkey_math:solver;

import :result;
import :types;

import <string>;
import <optional>;
import <stdexcept>;
import <iostream>;
import <deque>;

import <boost/algorithm/string/split.hpp>;
import <boost/algorithm/string/classification.hpp>;

using namespace monkey_math;

std::optional<std::pair<std::string, std::string> >
Result::ProcessLine( const std::string& _line )
{
	if( _line.length( ) < 7 )
		return std::nullopt;
	size_t pos = _line.find( ": " );
	if( pos == std::string::npos )
	{
		std::cerr << "Invalid line detected: " << _line << std::endl;
		throw std::runtime_error( "Line is not a valid operation" );
	}

	return std::make_pair( _line.substr( 0, pos ), _line.substr( pos + 2 ) );
}

void
Result::ProcessOne( const std::string& data )
{
	auto splitResult = ProcessLine( data );
	if( splitResult.has_value( ) )
		m_monkeys[ splitResult->first ] = splitResult->second;
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( Evaluate( m_monkeys, "root" ) );
}

void
Result::ProcessTwo( const std::string& data )
{
	ProcessOne( data );
}

std::string
Result::FinishPartTwo( )
{
	std::int64_t low = 0, high = std::numeric_limits<std::int64_t>::max( );
	MonkeyMath monkeys = m_monkeys;

	const auto it = monkeys.find( "root" );
	if( it == monkeys.end( ) )
	{
		std::cout << "Monkey [root] is not in the map!" << std::endl;
		throw std::logic_error( "No root!" );
	}
	const std::string& operation = it->second;

	if( operation.empty( ) )
	{
		std::cerr << "Monkey [root] has empty operation!" << std::endl;
		throw std::logic_error( "Empty operation line detected!" );
	}

	std::vector<std::string> parts;
	boost::split( parts, operation, boost::is_any_of( " " ) );

	if( parts.size( ) != 3 )
	{
		std::cerr << "Operation [" << operation << "] expected to have 3 parts but have " << parts.size( ) << std::endl;
		throw std::logic_error( "Operation has invalid number of parts!" );
	}
	if( parts[ 1 ].length( ) != 1 )
	{
		std::cerr << "Operator [" << parts[ 1 ] << "] expected to be of 1-length but is " << parts[ 1 ].length( ) << std::endl;
		throw std::logic_error( "Invalid operator!" );
	}

	const std::string leftMonkey = parts[ 0 ];
	const std::string rightMonkey = parts[ 2 ];

	// - First value is the coefficient of x (humn)
	// - Second value is the constant
	// This allows to represent linear equations of the form: coef*x + constant
	using Equation = std::pair<double, double>;

	// Forward declare so can be used inside
	std::function<Equation( const std::string& )> EvaluateEquation;

	EvaluateEquation = [&]( const std::string& name ) -> Equation {
		// If this is the "humn" node, it's our variable x with coefficient 1 and constant 0
		if( name == "humn" )
			return { 1.0, 0.0 }; // 1*x + 0

		const auto it = monkeys.find( name );
		if( it == monkeys.end( ) )
			throw std::logic_error( "Unknown monkey: " + name );

		const std::string& operation = it->second;

		if( operation.empty( ) )
			throw std::logic_error( "Empty operation for monkey: " + name );

		// If it's a number, return a constant expression (coefficient of x is 0)
		if( std::isdigit( operation.front( ) ) || operation.front( ) == '-' )
		{
			double value = std::stod( operation );
			return { 0.0, value }; // 0*x + value
		}

		// Otherwise, parse the operation
		std::vector<std::string> parts;
		boost::split( parts, operation, boost::is_any_of( " " ) );

		if( parts.size( ) != 3 )
			throw std::logic_error( "Operation has invalid number of parts: " + operation );

		// Evaluate both sides of the operation
		Equation lhs = EvaluateEquation( parts[ 0 ] );
		Equation rhs = EvaluateEquation( parts[ 2 ] );

		// Combine the equations based on the operation
		switch( parts[ 1 ][ 0 ] )
		{
		case '+':
			// (a*x + b) + (c*x + d) = (a+c)*x + (b+d)
			return { lhs.first + rhs.first, lhs.second + rhs.second };
		case '-':
			// (a*x + b) - (c*x + d) = (a-c)*x + (b-d)
			return { lhs.first - rhs.first, lhs.second - rhs.second };
		case '*':
		{
			// This is trickier. If we have linear equations, we need to distribute:
			// (a*x + b) * (c*x + d)
			// For simplicity, we'll assume one side has no x term (as in the example),
			// or we'd get a quadratic equation which is beyond the scope
			if( lhs.first != 0.0 && rhs.first != 0.0 )
				throw std::logic_error( "Multiplication of two expressions both containing x is not supported" );

			// If lhs has x: (a*x + b) * (0*x + d) = (a*d)*x + (b*d)
			if( lhs.first != 0.0 )
				return { lhs.first * rhs.second, lhs.second * rhs.second };

			// If rhs has x: (0*x + b) * (c*x + d) = (b*c)*x + (b*d)
			if( rhs.first != 0.0 )
				return { lhs.second * rhs.first, lhs.second * rhs.second };

			// If neither has x, it's just a constant
			return { 0.0, lhs.second * rhs.second };
		}
		case '/':
		{
			// Similar to multiplication, this is complex, but simplified with assumptions
			// We'll assume right side has no x term (as in the example)
			if( rhs.first != 0.0 )
				throw std::logic_error( "Division where the divisor contains x is not supported" );

			// (a*x + b) / (0*x + d) = (a/d)*x + (b/d)
			return { lhs.first / rhs.second, lhs.second / rhs.second };
		}
		default:
			throw std::logic_error( "Unhandled operator: " + parts[ 1 ] );
		}
		};

	// Evaluate both sides of the root equation
	Equation leftSide = EvaluateEquation( leftMonkey );
	Equation rightSide = EvaluateEquation( rightMonkey );

	std::cout << "Left side: " << leftSide.first << "*x + " << leftSide.second << std::endl;
	std::cout << "Right side: " << rightSide.first << "*x + " << rightSide.second << std::endl;

	// Now we need to solve the equation: leftSide = rightSide
	// If leftSide = a*x + b and rightSide = c*x + d
	// Then a*x + b = c*x + d
	// (a-c)*x = d-b
	// x = (d-b)/(a-c)

	double coeffDiff = leftSide.first - rightSide.first;
	double constDiff = rightSide.second - leftSide.second;

	if( std::abs( coeffDiff ) < 1e-10 )
	{
		// Coefficient difference is effectively zero
		if( std::abs( constDiff ) < 1e-10 )
		{
			// Both sides are equal, any value of x works
			return "Any value works";
		}
		else
		{
			// No solution exists
			return "No solution exists";
		}
	}

	// Calculate x = (d-b)/(a-c)
	double xValue = constDiff / coeffDiff;

	const std::int64_t result = static_cast< std::int64_t >( std::round( xValue ) );

	return std::to_string( result );
}

std::int64_t
Result::Evaluate( const MonkeyMath& _monkeys, const std::string& _name )
{
	const auto it = _monkeys.find( _name );
	if( it == _monkeys.end( ) )
	{
		std::cout << "Monkey [" << _name << "] is not in the map!" << std::endl;
		throw std::logic_error( "Unknown monkey!" );
	}
	const std::string& operation = it->second;

	if( operation.empty( ) )
	{
		std::cerr << "Monkey [" << _name << "] has empty operation!" << std::endl;
		throw std::logic_error( "Empty operation line detected!" );
	}

	if( std::isdigit( operation.front( ) ) || operation.front( ) == '-' )
		return std::atoll( operation.c_str( ) );

	std::vector<std::string> parts;
	boost::split( parts, operation, boost::is_any_of( " " ) );

	if( parts.size( ) != 3 )
	{
		std::cerr << "Operation [" << operation << "] expected to have 3 parts but have " << parts.size( ) << std::endl;
		throw std::logic_error( "Operation has invalid number of parts!" );
	}
	if( parts[ 1 ].length( ) != 1 )
	{
		std::cerr << "Operator [" << parts[ 1 ] << "] expected to be of 1-length but is " << parts[ 1 ].length( ) << std::endl;
		throw std::logic_error( "Invalid operator!" );
	}

	std::int64_t lhs = Evaluate( _monkeys, parts[ 0 ] ),
		rhs = Evaluate( _monkeys, parts[ 2 ] );

	switch( parts[ 1 ][ 0 ] )
	{
	case '+':
		return lhs + rhs;
	case '-':
		return lhs - rhs;
	case '*':
		return lhs * rhs;
	case '/':
		return lhs / rhs;
	default:
		std::cerr << "Operator [" << parts[ 1 ] << "] is not handled!" << std::endl;
		throw std::logic_error( "Unhnandled operator" );
	}
}
