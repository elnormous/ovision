namespace ov
{
    class Matrix final
    {
    public:
        Matrix() noexcept = default;
        
        Matrix(std::size_t w, std::size_t h, std::size_t c = 1):
            width{w},
            height{h},
            channels{c}
        {}
        
        ~Matrix()
        {
            if (data)
                switch (format)
                {
                    case Format::none: break;
                    case Format::float32: delete [] static_cast<float*>(data); break;
                    case Format::float64: delete [] static_cast<double*>(data); break;
                    case Format::int8: delete [] static_cast<std::int8_t*>(data); break;
                    case Format::int16: delete [] static_cast<std::int16_t*>(data); break;
                    case Format::int32: delete [] static_cast<std::int32_t*>(data); break;
                    case Format::uint8: delete [] static_cast<std::uint8_t*>(data); break;
                    case Format::uint16: delete [] static_cast<std::uint16_t*>(data); break;
                    case Format::uint32: delete [] static_cast<std::uint32_t*>(data); break;
                }
        }
        
        Matrix(Matrix&& other) noexcept:
            width{other.width},
            height{other.height},
            format{other.format},
            channels{other.channels},
            data{other.data}
        {
            other.width = 0;
            other.height = 0;
            other.format = Format::none;
            other.channels = 0;
            other.data = nullptr;
        }
        
        auto getWidth() const noexcept { return width; }
        auto getHeight() const noexcept { return height; }
        auto getChannels() const noexcept { return channels; }
        
    private:
        enum class Format
        {
            none,
            float32,
            float64,
            int8,
            int16,
            int32,
            uint8,
            uint16,
            uint32
        };
        
        std::size_t width = 0;
        std::size_t height = 0;
        Format format = Format::none;
        std::size_t channels = 0;
        void* data = nullptr;
    };
}
