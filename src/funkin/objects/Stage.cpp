#include "Stage.hpp"

#include "funkin/modding/LuaScript.hpp"

namespace funkin::objects{
    Stage::Stage(const std::string& stageName, const std::shared_ptr<Character>& boyfriend, const std::shared_ptr<Character>& dad) {
		this->stageName = stageName;
    	script = std::make_shared<modding::LuaScript>("assets/stages/" + stageName + "/stage.lua");
    	script->set("boyfriend", boyfriend);
    	script->set("dad", dad);
        script->call("onCreateStage", this);
    }

    Stage::~Stage() = default;
}