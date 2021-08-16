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
            channels{c}
        {}
        
        ~Matrix()
        {
            delete [] data;
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
