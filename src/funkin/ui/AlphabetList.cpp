#include "AlphabetList.hpp"
#include "funkin/Group.hpp"
#include "funkin/sound/SoundManager.hpp"

using Alphabet = funkin::objects::Alphabet;

namespace funkin {
	AlphabetList::AlphabetList(const float x,const float y) : Group(x, y) {}
	AlphabetList::AlphabetList() : Group(0, 0) {}

	AlphabetList::~AlphabetList() = default;

	void AlphabetList::update(float delta) {
		Group::update(delta);
	}
	void AlphabetList::add(std::shared_ptr<Alphabet> object) {
		members.push_back(object);
		alphabetMembers.push_back(object);
		object->isMenuItem=true;
		object->targetY = object->ID = members.size();
	}

	std::shared_ptr<Alphabet> AlphabetList::getSelected() {
		return alphabetMembers[currentSelected];
	}
	void AlphabetList::remove(std::shared_ptr<Alphabet> object) {
		if (auto ranges = std::ranges::find(members, object); ranges != members.end()) {
			members.erase(ranges);
		}
		if (auto ranges = std::ranges::find(alphabetMembers, object); ranges != alphabetMembers.end()) {
			alphabetMembers.erase(ranges);
		}
		changeSelection(0);
	}
	void AlphabetList::checkInput() {
		if (IsKeyPressed(KEY_DOWN)) {
			changeSelection(1);
		}else if (IsKeyPressed(KEY_UP)) {
			changeSelection(-1);
		}else if (GetMouseWheelMove() != 0){
			changeSelection(-static_cast<int>(GetMouseWheelMove()));
		}
	}
	void AlphabetList::changeSelection(const int change) {
		currentSelected = static_cast<std::uint8_t>(Wrap(static_cast<float>(currentSelected + change), 0, static_cast<float>(alphabetMembers.size())));
		if(change != 0){
			sound::SoundManager::playSound("assets/sounds/scrollMenu.ogg");
		}
		int i = 0;
		for (auto member: alphabetMembers) {
			if (member != nullptr) {
				member->targetY=i-this->currentSelected;
				member->visible=member->targetY > -10 && member->targetY < 10;
				member->color=(member->targetY == 0 ? WHITE : LIGHTGRAY);
				i++;
			}
		}

	}
} // namespace funkin
