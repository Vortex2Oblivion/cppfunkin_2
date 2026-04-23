#pragma once

#include <cstdint>
#include <functional>
#include <string>


namespace funkin::utilities
{
    class CoolUtil
    {
        public:
            /**
             * @see https://gist.github.com/dgoguerra/7194777
             */
            static std::string formatBytes(std::size_t bytes, std::uint8_t precision = 2);

    		static std::function<float(float)> easeFromString(std::string ease);

    		static char* ltrim(char* s);
    		static char* rtrim(char* s);
    		static char* trim(char* s);char * trim(const char * s);
	};
    
} // namespace funkin::utilities
