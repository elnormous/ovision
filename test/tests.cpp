#include <cstddef>
#include <vector>
#include "catch2/catch.hpp"
#include "Matrix.hpp"

TEST_CASE("Matrix constructor")
{
    const ov::Matrix<int> matrix{1, 2, 3};
    REQUIRE(matrix.getWidth() == 1);
    REQUIRE(matrix.getHeight() == 2);
    REQUIRE(matrix.getChannels() == 3);
}

TEST_CASE("Matrix move construction")
{
    ov::Matrix<int> matrix{1, 2, 3};
    ov::Matrix<int> other = std::move(matrix);

    REQUIRE(matrix.getWidth() == 0);
    REQUIRE(matrix.getHeight() == 0);
    REQUIRE(matrix.getChannels() == 0);

    REQUIRE(other.getWidth() == 1);
    REQUIRE(other.getHeight() == 2);
    REQUIRE(other.getChannels() == 3);
}

TEST_CASE("Matrix value construction")
{
    const ov::Matrix<int> matrix{1, 2, 3,
        0, 1, 2, 3, 4, 5
    };

    REQUIRE(matrix.getWidth() == 1);
    REQUIRE(matrix.getHeight() == 2);
    REQUIRE(matrix.getChannels() == 3);

    std::size_t count = 0;

    for (int v : matrix)
    {
        REQUIRE(v == static_cast<int>(count));
        ++count;
    }

    REQUIRE(count == 6);
}

TEST_CASE("Matrix move assignment")
{
    ov::Matrix<int> matrix{1, 2, 3};
    ov::Matrix<int> other;
    other = std::move(matrix);

    REQUIRE(matrix.getWidth() == 0);
    REQUIRE(matrix.getHeight() == 0);
    REQUIRE(matrix.getChannels() == 0);

    REQUIRE(other.getWidth() == 1);
    REQUIRE(other.getHeight() == 2);
    REQUIRE(other.getChannels() == 3);
}

TEST_CASE("Matrix const range loop")
{
    const ov::Matrix<int> matrix{1, 2, 3};

    std::size_t count = 0;

    for (int v : matrix)
    {
        REQUIRE(v == 0);
        ++count;
    }

    REQUIRE(count == 6);
}

TEST_CASE("Matrix range loop")
{
    ov::Matrix<int> matrix{1, 2, 3};

    std::size_t count = 0;

    for (int& v : matrix)
    {
        v = static_cast<int>(count);
        ++count;
    }

    REQUIRE(count == 6);
    count = 0;

    for (int v : matrix)
    {
        REQUIRE(v == static_cast<int>(count));
        ++count;
    }

    REQUIRE(count == 6);
}

TEST_CASE("Matrix copy constructor")
{
    const ov::Matrix<int> matrix{1, 2, 3,
        0, 1, 2, 3, 4, 5
    };

    const ov::Matrix<int> matrix2 = matrix;

    std::size_t count = 0;
    for (int v : matrix2)
    {
        REQUIRE(v == static_cast<int>(count));
        ++count;
    }

    REQUIRE(count == 6);
}

TEST_CASE("Matrix assignment")
{
    const ov::Matrix<int> matrix{1, 2, 3,
        0, 1, 2, 3, 4, 5
    };

    ov::Matrix<int> matrix2;
    matrix2 = matrix;

    std::size_t count = 0;

    for (int v : matrix2)
    {
        REQUIRE(v == static_cast<int>(count));
        ++count;
    }

    REQUIRE(count == 6);
}

TEST_CASE("Matrix comparison equal")
{
    const ov::Matrix<int> matrix1{1, 2, 3,
        0, 1, 2, 3, 4, 5
    };

    const ov::Matrix<int> matrix2{1, 2, 3,
        0, 1, 2, 3, 4, 5
    };

    REQUIRE(matrix1 == matrix2);
}

TEST_CASE("Matrix comparison different size")
{
    const ov::Matrix<int> matrix1{1, 2, 2,
        0, 1, 2, 3
    };

    const ov::Matrix<int> matrix2{1, 2, 3,
        0, 1, 2, 3, 4, 5
    };

    REQUIRE_FALSE(matrix1 == matrix2);
}
