#include <algorithm>

namespace ov
{
    template <class T>
    class Matrix final
    {
    public:
        Matrix() noexcept = default;

        Matrix(std::size_t w, std::size_t h, std::size_t c = 1):
            width{w},
            height{h},
            channels{c},
            data{new T[w * h * c]{}}
        {}

        ~Matrix()
        {
            delete [] data;
        }

        Matrix(const Matrix& other):
            width{other.width},
            height{other.height},
            channels{other.channels},
            data{new T[other.width * other.height * other.channels]}
        {
            std::copy(other.data,
                      other.data + other.width * other.height * other.channels,
                      data);
        }

        Matrix(Matrix&& other) noexcept:
            width{other.width},
            height{other.height},
            channels{other.channels},
            data{other.data}
        {
            other.width = 0;
            other.height = 0;
            other.channels = 0;
            other.data = nullptr;
        }

        Matrix& operator=(const Matrix& other)
        {
            delete [] data;

            width = other.width;
            height = other.height;
            channels = other.channels;
            data = new T[other.width * other.height * other.channels];
            std::copy(other.data,
                      other.data + other.width * other.height * other.channels,
                      data);

            return *this;
        }

        Matrix& operator=(Matrix&& other) noexcept
        {
            delete [] data;

            width = other.width;
            height = other.height;
            channels = other.channels;
            data = other.data;

            other.width = 0;
            other.height = 0;
            other.channels = 0;
            other.data = nullptr;

            return *this;
        }

        auto begin() const noexcept
        {
            return data;
        }

        auto end() const noexcept
        {
            return data + width * height * channels;
        }

        auto begin() noexcept
        {
            return data;
        }

        auto end() noexcept
        {
            return data + width * height * channels;
        }

        auto getWidth() const noexcept { return width; }
        auto getHeight() const noexcept { return height; }
        auto getChannels() const noexcept { return channels; }

    private:
        std::size_t width = 0;
        std::size_t height = 0;
        std::size_t channels = 0;
        T* data = nullptr;
    };
}
