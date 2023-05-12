#pragma once

template<typename T>
class Singleton
{
private:
	static T Instance;

protected:
	/** Constructor */
	Singleton() = default;

public:
	/** Copy Constructor */
	Singleton(const Singleton&) = delete;

	/** Operator = */
	Singleton& operator = (const Singleton&) = delete;

	/** Getters */
	static T& GetInstance() 
	{
		return Instance; 
	}
};

