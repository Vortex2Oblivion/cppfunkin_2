#pragma once

#include <cstddef>


namespace funkin::utilities {
	class ProcessInfo {
        public:
            /**
             * @see
             * https://web.archive.org/web/20190923225212/http://nadeausoftware.com/articles/2012/07/c_c_tip_how_get_process_resident_set_size_physical_memory_use
             */
            static size_t getMemoryUsage();
            /**
             * @see
             * https://web.archive.org/web/20190923225212/http://nadeausoftware.com/articles/2012/07/c_c_tip_how_get_process_resident_set_size_physical_memory_use
             */
            static size_t getMemoryPeak();
	};

} // namespace funkin::utilities
