#pragma once
#include "funkin/Group.hpp"
#include "funkin/objects/Alphabet.hpp"


namespace funkin {
	using Alphabet = objects::Alphabet;
	class AlphabetList : public Group<Alphabet> {
	public:
		AlphabetList(float x, float y);
		explicit AlphabetList();
		~AlphabetList() override;

		void add(const std::shared_ptr<Alphabet> &object);
		void remove(const std::shared_ptr<Alphabet> &object);
		void changeSelection(int change);
		bool checkInput();
		[[nodiscard]] std::shared_ptr<Alphabet> getSelected() const;

		int currentSelected = 0;
	};
} // namespace funkin
