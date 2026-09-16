#include "AlphabetList.hpp"
#include "funkin/Group.hpp"
#include "funkin/sound/SoundManager.hpp"

using Alphabet = funkin::objects::Alphabet;

namespace funkin {
	AlphabetList::AlphabetList(const float x, const float y) : Group(x, y) {}
	AlphabetList::AlphabetList() : Group(0, 0) {}

	AlphabetList::~AlphabetList() = default;

	void AlphabetList::add(const std::shared_ptr<Alphabet> &object) {
		members.push_back(object);
		object->isMenuItem = true;
		object->targetY = static_cast<int>(members.size());
		object->ID = members.size();
	}

	std::shared_ptr<Alphabet> AlphabetList::getSelected() const { return members[currentSelected]; }

	void AlphabetList::remove(const std::shared_ptr<Alphabet> &object) {
		Group::remove(object);
		changeSelection(0);
	}
	bool AlphabetList::checkInput() {
		if (IsKeyPressed(KEY_DOWN)) {
			changeSelection(1);
			return true;
		}
		if (IsKeyPressed(KEY_UP)) {
			changeSelection(-1);
			return true;
		}
		if (GetMouseWheelMove() != 0) {
			changeSelection(-static_cast<int>(GetMouseWheelMove()));
			return true;
		}
		return false;
	}
	void AlphabetList::changeSelection(const int change) {
		currentSelected = static_cast<std::uint8_t>(Wrap(static_cast<float>(currentSelected + change), 0, static_cast<float>(size())));
		if (change != 0)
			sound::SoundManager::playSound("assets/sounds/scrollMenu.ogg");

		int i = 0;
		for (const auto &member: members) {
			if (member != nullptr) {
				member->targetY = i - this->currentSelected;
				member->alpha = member->targetY == 0 ? 1.0f : 0.8f;
				i++;
			}
		}
	}
} // namespace funkin
