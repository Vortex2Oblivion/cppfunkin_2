#pragma once
#include "funkin/Group.hpp"
#include "funkin/objects/Alphabet.hpp"

using Alphabet = funkin::objects::Alphabet;

namespace funkin {
	class AlphabetList : public Group<> {
	public:
		AlphabetList(const float x,const float y);
		explicit AlphabetList();
		~AlphabetList() override;

		void update(float delta) override;


		void add(const std::shared_ptr<Alphabet> object);
		void remove(const std::shared_ptr<Alphabet> object);
		void changeSelection(const int change);
		bool checkInput();
		std::shared_ptr<Alphabet> getSelected() const;


		int currentSelected = 0;
		/* TODO: This should be implemented better*/
		std::vector<std::shared_ptr<Alphabet>> alphabetMembers = {};

	// protected:
		// virtual void create();
	};
} // namespace funkin
