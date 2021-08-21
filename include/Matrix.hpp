#include <algorithm>

namespace ov
{
    template <class T>
    class Iterator final
    {
    public:
        Iterator(T* v) noexcept: value{v} {}

        [[nodiscard]] bool operator==(const Iterator& other) const noexcept { return value == other.value; }
        [[nodiscard]] bool operator!=(const Iterator& other) const noexcept { return value != other.value; }

        [[nodiscard]] T& operator*() noexcept { return *value; }
        [[nodiscard]] const T& operator*() const noexcept { return *value; }

        [[nodiscard]] Iterator& operator++() noexcept
        {
            value++;
            return *this;
        }

        [[nodiscard]] Iterator& operator++(int) noexcept
        {
            auto result = *this;
            value++;
            return result;
        }

    private:
        T* value;
    };

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

        template <typename ...A>
        Matrix(std::size_t w, std::size_t h, std::size_t c, const A... args):
            width{w},
            height{h},
            channels{c},
            data{new T[w * h * c]{args...}}
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

        [[nodiscard]] auto begin() const noexcept
        {
            return Iterator<const T>{data};
        }

        [[nodiscard]] auto end() const noexcept
        {
            return Iterator<const T>{data + width * height * channels};
        }

        [[nodiscard]] auto begin() noexcept
        {
            return Iterator<T>{data};
        }

        [[nodiscard]] auto end() noexcept
        {
            return Iterator<T>{data + width * height * channels};
        }

        [[nodiscard]] auto getWidth() const noexcept { return width; }
        [[nodiscard]] auto getHeight() const noexcept { return height; }
        [[nodiscard]] auto getChannels() const noexcept { return channels; }

        [[nodiscard]] bool operator==(const Matrix& other) const noexcept
        {
            if (width != other.width ||
                height != other.height ||
                channels != other.channels)
                return false;

            return std::equal(data, data + width * height * channels, other.data);
        }

    private:
        std::size_t width = 0;
        std::size_t height = 0;
        std::size_t channels = 0;
        T* data = nullptr;
    };
}
