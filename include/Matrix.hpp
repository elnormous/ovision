namespace ov
{
    class Matrix final
    {
    public:
        Matrix() = default;
        
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
        
        Matrix(std::size_t w, std::size_t h):
            width{w},
            height{h}
        {}
        
        auto getWidth() const noexcept { return width; }
        auto getHeight() const noexcept { return height; }
        
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
