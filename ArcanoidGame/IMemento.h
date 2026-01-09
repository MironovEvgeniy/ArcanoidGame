#pragma once
#include <memory>

class IMemento
{
public:
	virtual ~IMemento() = default;
};

class IMementoOriginator
{
public:
	virtual ~IMementoOriginator() = default;

	virtual std::shared_ptr<IMemento> Save() const = 0;
	virtual void Restore(std::shared_ptr<IMemento> memento) = 0;
};

class IMementoCareTaker
{
public:
	virtual ~IMementoCareTaker() = default;

	virtual void Store(std::shared_ptr<IMemento> memento) = 0;
	virtual std::shared_ptr<IMemento> Get() const = 0;
};