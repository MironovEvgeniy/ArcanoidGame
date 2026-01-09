#pragma once
#include "IMemento.h"
#include <vector>

namespace ArcanoidGame
{
	class SaveSystem final : public IMementoCareTaker
	{
	private:
		std::vector<std::shared_ptr<IMemento>> mementoList;

	public:
		virtual void Store(std::shared_ptr<IMemento> memento) override { mementoList.push_back(memento); };

		virtual std::shared_ptr<IMemento> Get() const override {
			//if (mementoList.empty()) return nullptr;
			return mementoList.back();
		};
	};
}