#include "Save.hpp"

#include "raylib.h"

namespace funkin::utilities {
	Save::Save(const std::string &saveName) {
		const char *saveDirectory = "save";
		const char *savePath = TextFormat("%s/%s.json", saveDirectory, saveName.c_str());
		if (!DirectoryExists(saveDirectory)) {
			MakeDirectory(saveDirectory);
		}
		if (!FileExists(savePath)) {
			SaveFileText(savePath, "");
		}
	}

	Save::~Save() {}
} // namespace funkin::utilities
