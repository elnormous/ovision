#include <memory>

namespace ov
{
    class Matrix final
    {
    public:
        Matrix() = default;

    private:
        enum class Format
        {
            float32,
            float64,
            int8,
            int16,
            int32,
            uint8,
            uint16,
            uint32
        };

        std::uint32_t format = 0;
        std::size_t width = 0;
        std::size_t height = 0;
        std::size_t channels = 0;
        std::unique_ptr<void*> data;
    };
}
