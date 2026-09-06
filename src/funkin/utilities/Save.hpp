#pragma once
#include <string>
#include "nlohmann/json.hpp"

namespace funkin::utilities {
	class Save {
		using json = nlohmann::json;

	public:
		explicit Save(const std::string &saveName);
		~Save();

		void flush() const;

	private:
		json save = {};
		std::string savePath;
	};
} // namespace funkin::utilities
