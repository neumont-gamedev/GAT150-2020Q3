#pragma once

template<typename T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton) = delete;

	T* operator->() { return Instance(); }
	const T* operator->() const { return Instance(); }

	T& operator*() { return *Instance(); }
	const T& operator*() const { return *Instance(); }

	static T* Instance();

private:
	Singleton() {}
	virtual ~Singleton() {}

private:
	static T* m_instance;
};

template<typename T> 
T* Singleton<T>::m_instance = nullptr;

template<typename T>
T* Singleton<T>::Instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new T;
	}

	return m_instance;
}