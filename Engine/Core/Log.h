#pragma once
#include <string>

namespace nc
{
	class LogFile
	{
	public:
		static FILE*& Stream();
		static void Output(const std::string& msg);
	};

	inline FILE*& LogFile::Stream()
	{
		static FILE* pStream = stderr;
		return pStream;
	}

	inline void LogFile::Output(const std::string& msg)
	{
		FILE* pStream = Stream();
		if (!pStream)
			return;
		fprintf(pStream, "%s", msg.c_str());
		fflush(pStream);
	}

	template<typename T>
	class Log
	{
	public:
		std::ostringstream& Get();

	protected:
		std::ostringstream m_stream;
	};

	template <typename T>
	std::ostringstream& Log<T>::Get()
	{
		//os << "- " << NowTime();
		//os << " " << ToString(level) << ": ";
		//os << std::string(level > ldebug ? level - ldebug : 0, '\t');
		return m_stream;
	}

	//class ConsoleLogImpl : public ILog
	//{
	//public:
	//	virtual void Open(const std::string& name) override;
	//	virtual void Close() override;
	//	virtual void Write(const std::string& text) override;
	//	virtual void Write(const char* format, ...) override;
	//};

}
