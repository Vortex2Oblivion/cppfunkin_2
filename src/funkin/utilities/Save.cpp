#include "Save.hpp"

#include "raylib.h"

namespace funkin::utilities {
	Save::Save(const std::string &saveName) {
		constexpr auto saveDirectory = "save";
		savePath = TextFormat("%s/%s.json", saveDirectory, saveName.c_str());

		flush();

		auto fileText = LoadFileText(savePath.c_str());
		save = json::parse(fileText);
		UnloadFileText(fileText);

		flush();
	}

	Save::~Save() = default;

	void Save::flush() const {
		constexpr auto saveDirectory = "save";

		if (!DirectoryExists(saveDirectory)) {
			MakeDirectory(saveDirectory);
		}
		if (!FileExists(savePath.c_str())) {
			SaveFileText(savePath.c_str(), save.dump().c_str());
		}
	}
} // namespace funkin::utilities
