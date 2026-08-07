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

    		static std::string trim(std::string str);

    		static std::vector<std::string> split(std::string str, const std::string& delimiter);

    		static bool randomBool(float chance);
	};
    
} // namespace funkin::utilities
