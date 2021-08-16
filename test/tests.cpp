#include <cstddef>
#include <vector>
#include "catch2/catch.hpp"
#include "Matrix.hpp"

TEST_CASE("Matrix constructor")
{
    ov::Matrix matrix{1, 2, 3};
    REQUIRE(matrix.getWidth() == 1);
    REQUIRE(matrix.getHeight() == 2);
    REQUIRE(matrix.getChannels() == 3);
}

TEST_CASE("Matrix move")
{
    ov::Matrix matrix{1, 2, 3};
    ov::Matrix other = std::move(matrix);
    
    REQUIRE(matrix.getWidth() == 0);
    REQUIRE(matrix.getHeight() == 0);
    REQUIRE(matrix.getChannels() == 0);
    
    REQUIRE(other.getWidth() == 1);
    REQUIRE(other.getHeight() == 2);
    REQUIRE(other.getChannels() == 3);
}
