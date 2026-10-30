#include "Stage.hpp"


#include "funkin/modding/PlutoScript.hpp"

namespace funkin::objects {
	Stage::Stage(const std::string &stageName, const std::shared_ptr<Character> &boyfriend, const std::shared_ptr<Character> &dad,
				 const std::shared_ptr<Character> &girlfriend) {

		this->stageName = stageName;
		if (!FileExists(("assets/stages/" + stageName + "/stage.pluto").c_str())) {
			TraceLog(5, ("Unable to load stage '" + stageName + "'. Fallbacking to mainStage").c_str());
			this->stageName = "mainStage";
		}
		script = std::make_shared<modding::PlutoScript>("assets/stages/" + this->stageName + "/stage.pluto");
		script->set("boyfriend", boyfriend);
		script->set("dad", dad);
		script->set("girlfriend", girlfriend);
		script->call("onCreateStage", this);
	}

	Stage::~Stage() = default;

	void Stage::snapToPosition(const std::shared_ptr<Character> &character, const float x, const float y) {
		character->updateHitbox();
		character->position.x = x - character->hitbox.width / 2;
		character->position.y = y - character->hitbox.height;
	}
} // namespace funkin::objects
