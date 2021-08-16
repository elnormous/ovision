#include <cstddef>
#include <vector>
#include "catch2/catch.hpp"
#include "Matrix.hpp"

TEST_CASE("Matrix")
{
    ov::Matrix matrix{1, 2, 3};
    REQUIRE(matrix.getWidth() == 1);
    REQUIRE(matrix.getHeight() == 2);
    REQUIRE(matrix.getChannels() == 3);
}
