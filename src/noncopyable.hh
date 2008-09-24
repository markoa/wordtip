
#ifndef WORDTIP_NONCOPYABLE_HH
#define WORDTIP_NONCOPYABLE_HH

namespace wordtip {

    class NonCopyable
    {
    protected:
        NonCopyable() {}
        ~NonCopyable() {}
    
    private:
        NonCopyable(const NonCopyable& );
        const NonCopyable& operator=(const NonCopyable& );
    };

} // namespace wordtip

#endif  // WORDTIP_NONCOPYABLE_HH
