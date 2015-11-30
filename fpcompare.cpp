#include <gtest/gtest.h>


namespace fp {
	int NumberOfEqualFractionals(double a, double b)
	{
		if (a == b) {
			return -1;
		}

		if (std::abs(a) == std::abs(b)) {
			return 0;
		}

		const int exp_a = std::ilogb(a);
		const int exp_b = std::ilogb(b);
		const int exp_r = std::ilogb(std::abs(a) - std::abs(b));

		return std::max(exp_a, exp_b) - exp_r - 1;
	}

	bool equals(double a, double b, int threshold)
	{
		if( a == b ) return true;

		if (NumberOfEqualFractionals(a, b) >= threshold) return true;

		return false;
	}
}


using namespace testing;

const double fractions[] = {
	8, 4, 2, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.0078125, 0.00390625
};

TEST(FractionalDifference, MinusOneForSameNumber)
{
	const double aNumber = 1;

	ASSERT_EQ(-1, fp::NumberOfEqualFractionals(aNumber, aNumber));
}

TEST(FractionalDifference, CorrectValueWhenFirstBitDiffers)
{
	const double aNumber = fractions[10];
	const double anOtherNumber = fractions[0];

	ASSERT_EQ(0, fp::NumberOfEqualFractionals(aNumber, anOtherNumber));
}

TEST(FractionalDifference, CorrectValueWhenOppositeSign)
{
	const double aNumber = -fractions[0];
	const double anOtherNumber = fractions[0];

	ASSERT_EQ(0, fp::NumberOfEqualFractionals(aNumber, anOtherNumber));
}

TEST(FractionalDifference, CorrectValueWhenSignDiffers)
{
	const double aNumber = -fractions[10];
	const double anOtherNumber = fractions[0];

	ASSERT_EQ(0, fp::NumberOfEqualFractionals(aNumber, anOtherNumber));
}

TEST(FractionalDifference, CorrectValueWhenLowerBitDiffers)
{
	const double aNumber = fractions[0] + fractions[1] + fractions[2] + fractions[3];
	const double anOtherNumber = fractions[0] + fractions[1] + fractions[2] + fractions[4];

	ASSERT_EQ(3, fp::NumberOfEqualFractionals(aNumber, anOtherNumber));
}

TEST(FractionalDifference, CorrectValueWhenOverflow)
{
	const double aNumber = fractions[0];
	const double anOtherNumber = fractions[1] + fractions[2] + fractions[3] + fractions[4] + fractions[5] + fractions[6] + fractions[7] + fractions[8] + fractions[9] + fractions[10] + fractions[11];

	ASSERT_EQ(10, fp::NumberOfEqualFractionals(aNumber, anOtherNumber));
}

TEST(FloatingPointCompare, ANumberIsEqualToItself)
{
	const double aNumber = 123;

	ASSERT_TRUE(fp::equals(aNumber, aNumber, 0));
}

TEST(FloatingPointCompare, DifferentNumbersEqualIfInsideThreshold)
{
	const double aNumber = fractions[0] + fractions[1] + fractions[2] + fractions[3];
	const double anOtherNumber = fractions[0] + fractions[1] + fractions[2] + fractions[4];

	ASSERT_TRUE(fp::equals(aNumber, anOtherNumber, 3));
}

TEST(FloatingPointCompare, DifferentNumbersDiffersIfOutsideThreshold)
{
	const double aNumber = fractions[0] + fractions[1] + fractions[2] + fractions[3];
	const double anOtherNumber = fractions[0] + fractions[1] + fractions[2] + fractions[4];

	ASSERT_FALSE(fp::equals(aNumber, anOtherNumber, 4));
}
