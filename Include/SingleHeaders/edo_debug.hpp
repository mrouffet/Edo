// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_SH_DEBUG_GUARD
#define EDO_SH_DEBUG_GUARD

#include <cstdint>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <sys/stat.h>
#include <filesystem>
#include <unordered_map>
#include <source_location>

#if !defined(NDEBUG) || defined(_DEBUG)

	/// Edo Debug preprocessor.
	#define EDO_DEBUG 1

#else

	/// Edo Debug preprocessor.
	#define EDO_DEBUG 0

#endif

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)

	#include <Windows.h>

	#define EDO_DEBUG_WIN 1
#else

	#define EDO_DEBUG_WIN 0

#endif

namespace edo
{
// ##############################################################################################################################
// #													TYPES																	#
// ##############################################################################################################################

// ##############################################################
// #					TO-STRING								#
// ##############################################################

//{ ToString

	namespace intl
	{
		/**
		*	\brief Internal Binary ToString implementation.
		* 
		*	Convert bit array into hex values.
		* 
		*	\param[in] _data	Bit array to convert.
		*	\param[in] _size	Size of the bit array.
		* 
		*	\return	string of bit array as hex values.
		*/
		std::string ToStringBinary(const char* _data, uint64_t _size) noexcept;
	}

	/**
	*	\brief Binary ToString implementation.
	*
	*	Convert elem into bit array and print as hex values.
	* 
	*	\tparam T			Type of element.
	*	\param[in] _elem	Element to convert to string.
	* 
	*	\return	std::string from element converted in binary.
	*/
	template <typename T>
	std::string ToStringBinary(const T& _elem) noexcept
	{
		return intl::ToStringBinary(reinterpret_cast<const char*>(&_elem), sizeof(T));
	}


	/**
	*	\brief ToString default implementation used to print elem.
	* 
	*	Convert basic types to string, otherwise make binary conversion.
	* 
	*	\tparam T			Type of element.
	*	\param[in] _elem	Element to convert to string.
	*
	*	\return	std::string from element converted.
	*/
	template <typename T>
	std::string ToString(const T& _elem)
	{
		if constexpr (std::is_same<T, char>::value)
		{
			return std::string(1u, _elem);
		}
		else if constexpr (std::is_arithmetic<T>::value)
		{
			return std::to_string(_elem);
		}
		else if constexpr (std::is_same<T, std::string>::value)
		{
			return std::forward<T>(_elem);
		}
		else
		{
			return ToStringBinary(_elem);
		}
	}

	/**
	*	\brief ToString implementation used to print a pointer.
	*
	*	\tparam T			Type of the pointer.
	*	\param[in] _ptr		Pointer to convert to string.
	*
	*	\return	std::string from pointer converted.
	*/
	template <typename T>
	std::string ToString(T* _ptr)
	{
		if constexpr (std::is_same<T*, char*>::value || std::is_same<T*, const char*>::value)
		{
			return std::string(_ptr);
		}
		else
		{
			return "0x" + std::to_string(reinterpret_cast<uint64_t>(_ptr));
		}
	}

	/**
	*	\brief ToString implementation used to print an array.
	*
	*	\tparam T			Type of the array.
	*	\param[in] _elems	Array pointer to convert to string.
	*	\param[in] _size	Size of the array.
	*
	*	\return	std::string from array converted.
	*/
	template <typename T>
	std::string ToString(const T* _elems, uint64_t _size)
	{
		std::string res = "[size:" + std::to_string(_size) + "]{ ";

		for (uint32_t i = 0; i < _size; ++i)
			res += ToString(_elems[i]) + " | ";

		res[res.size() - 2] = ' ';
		res[res.size() - 1] = '}';

		return res;
	}

	/**
	*	\brief ToString implementation used to print a vector.
	*
	*	\tparam T			Type of the vector.
	*	\param[in] _vec		Vector to convert to string.
	*
	*	\return	std::string from vector converted.
	*/
	template <typename T>
	std::string ToString(const std::vector<T>& _vec)
	{
		return ToString(_vec.data(), _vec.size());
	}

#if EDO_DEBUG_IMPLEMENTATION

	namespace intl
	{
		std::string ToStringBinary(const char* _data, uint64_t _size) noexcept
		{
			static constexpr char table[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

			std::string res;

			res.reserve(3 * _size + 1);

			res += '<';

			for (const char* it = _data + _size - 1; it >= _data; --it)
			{
				res += table[(*it & 0xF0) >> 4];
				res += table[*it & 0x0F];

				res += '-';
			}

			res.back() = '>';

			return res;
		}
	}

	std::string ToString(const tm& _tm)
	{
		return
			std::to_string(_tm.tm_mday) + '.' +
			std::to_string(_tm.tm_mon + 1) + '.' +		// January is month 1.
			std::to_string(_tm.tm_year + 1900) + '-' +	// tm_year is the year since 1900.
			std::to_string(_tm.tm_hour) + 'h' +
			std::to_string(_tm.tm_min) + 'm' +
			std::to_string(_tm.tm_sec) + 's';
	}

#endif // EDO_DEBUG_IMPLEMENTATION

//}


//{ ToWString

	namespace intl
	{
		std::wstring ConvertCStringToWString(const char* _cstr, uint64_t _size = uint64_t(-1));
	
		inline std::wstring ConvertStringToWString(const std::string& _str)
		{
			return ConvertCStringToWString(_str.c_str(), _str.size());
		}
	}

	/**
	*	\brief ToWString default implementation used to print elem.
	* 
	*	Convert basic types to wstring, otherwise make binary conversion.
	* 
	*	\tparam T			Type of element.
	*	\param[in] _elem	Element to convert to wstring.
	*
	*	\return	std::wstring from element converted.
	*/
	template <typename T>
	std::wstring ToWString(const T& _elem) noexcept
	{
		if constexpr (std::is_same<T, char>::value)
		{
			return std::wstring(1u, _elem);
		}
		if constexpr (std::is_same<T, wchar_t>::value)
		{
			return std::wstring(1u, _elem);
		}
		else if constexpr (std::is_arithmetic<T>::value)
		{
			return std::to_wstring(_elem);
		}
		else if constexpr (std::is_same<T, std::string>::value)
		{
			return intl::ConvertStringToWString(_elem);
		}
		else if constexpr (std::is_same<T, std::wstring>::value)
		{
			return std::forward<T>(_elem);
		}
		else
		{
			// Search for ToString definition for elem.
			return intl::ConvertStringToWString(ToString(_elem));
		}
	}

	/**
	*	\brief ToWString implementation used to print a pointer.
	*
	*	\tparam T			Type of pointer.
	*	\param[in] _ptr		Pointer to convert to wstring.
	*
	*	\return	std::wstring from pointer converted.
	*/
	template <typename T>
	std::wstring ToWString(T* _ptr) noexcept
	{
		if constexpr (std::is_same<T*, char*>::value || std::is_same<T*, const char*>::value)
		{
			return intl::ConvertCStringToWString(_ptr);
		}
		else if constexpr (std::is_same<T*, wchar_t*>::value || std::is_same<T*, const wchar_t*>::value)
		{
			return std::wstring(_ptr);
		}
		else
		{
			return "0x" + std::to_wstring(reinterpret_cast<uint64_t>(_ptr));
		}
	}

	/**
	*	\brief ToWString implementation used to print an array.
	*
	*	\tparam T			Type of the array.
	*	\param[in] _elems	Array pointer to convert to wstring.
	*	\param[in] _size	Size of the array.
	*
	*	\return	std::wstring from array converted.
	*/
	template <typename T>
	std::wstring ToWString(const T* _elems, uint64_t _size)
	{
		std::wstring res = L"[size:" + std::to_wstring(_size) + L"]{ ";

		for (uint32_t i = 0; i < _size; ++i)
			res += ToWString(_elems[i]) + L", ";

		res[res.size() - 2] = L' ';
		res[res.size() - 1] = L'}';

		return res;
	}

	/**
	*	\brief ToWString implementation used to print a vector.
	*
	*	\tparam T			Type of the vector.
	*	\param[in] _vec		Vector to convert to wstring.
	*
	*	\return	std::wstring from vector converted.
	*/
	template <typename T>
	std::wstring ToWString(const std::vector<T>& _vec)
	{
		return ToWString(_vec.data(), _vec.size());
	}

#if EDO_DEBUG_IMPLEMENTATION

	namespace intl
	{
		std::wstring ConvertCStringToWString(const char* _cstr, uint64_t _size)
		{
		#if EDO_DEBUG_WIN

			// strlen does not count '\0'
			const uint64_t srcByteSize = (_size != uint64_t(-1) ? _size : strlen(_cstr)) * sizeof(char);

			if (srcByteSize == 0)
				return std::wstring();

			// Compute converted size.
			const int wsize = MultiByteToWideChar(CP_UTF8, 0, _cstr, static_cast<int>(srcByteSize), nullptr, 0);

			std::wstring out;
			out.resize(wsize);

			// Convert.
			const int res = MultiByteToWideChar(CP_UTF8, 0, _cstr, static_cast<int>(srcByteSize), out.data(), wsize);
			(void)res;

			#if EDO_DEBUG

				// Function failed.
				if (res == 0)
					return std::wstring(L"Invalid ToWString conversion. Error code [" + std::to_wstring(GetLastError()) + L"]");

			#endif

			return out;

		#endif // EDO_DEBUG_WIN
		}
	}

#endif // EDO_DEBUG_IMPLEMENTATION

//}


//{ Formatting

	namespace intl
	{
		template <typename StringT>
		uint32_t ReplaceAllInString(StringT& _str, const StringT& _what, const StringT& _with) {

			uint32_t count = 0u;

			for (typename StringT::size_type pos{}; (pos = _str.find(_what, pos)) != _str.npos; pos += _with.size())
			{
				_str.replace(pos, _what.size(), _with);
				++count;
			}

			return count;
		}

		template <typename FirstT, typename... Args>
		void StringFormatImpl(std::wstring& _str, uint32_t _depth, FirstT&& _first, Args&&... _args)
		{
			const uint32_t count = intl::ReplaceAllInString(_str, L'%' + std::to_wstring(_depth), ToWString(_first));

			// No more args to parse.
			// Must be constexpr for valid recursive compilation.
			if constexpr (sizeof...(Args) == 0)
				return;
			else
			{
				// No more token to parse.
				if (!count)
					return;

				StringFormatImpl(_str, _depth + 1, std::forward<Args>(_args)...);
			}
		}
	}

	template <typename FirstT, typename... Args>
	std::wstring StringFormat(FirstT _first, Args&&... _args)
	{
		// Force convert to wstring. Input might be string or any object.
		std::wstring str = ToWString(std::forward<FirstT>(_first));

		// Arguments means string formatting.
		if constexpr (sizeof...(Args) != 0)
			intl::StringFormatImpl(str, 1u, std::forward<Args>(_args)...);

		return str;
	}

//}

// ##############################################################


// ##############################################################
// #					LOG LEVEL								#
// ##############################################################

	/// \brief All levels of logging.
	enum class LogLevel : uint8_t
	{
		/// Normal level
		Normal = (1 << 0),

		/// Info level
		Info = (1 << 1),

		/// Warning level
		Warning = (1 << 2),

		/// Error level
		Error = (1 << 3),

		/// Assertion Success level
		AssertSuccess = (1 << 4),

		/// Assertion Failure level
		AssertFailure = (1 << 5),

		/// Default log level (no assert success).
		Default = Normal | Info | Warning | Error | AssertFailure,

		Max = uint8_t(-1)
	};

	/// Shortcut alias.
	using LogLvl = LogLevel;

#if EDO_DEBUG_IMPLEMENTATION

	namespace intl
	{
		uint32_t ScanLogLevel(LogLevel _lvl)
		{
			const uint32_t ulvl = static_cast<uint32_t>(_lvl);

			unsigned long index = 0u;

		#if _MSC_VER

			_BitScanForward64(&index, ulvl);

		#else

			// __builtin_ffs returns 1 + index if non zero.
			index = __builtin_ffs(ulvl) - 1;

		#endif

			return static_cast<uint32_t>(index);
		}
	}

	std::string ToString(LogLevel _lvl) noexcept
	{
		static constexpr const char* const names[]{
			"Unknown",
			"Normal",
			"Info",
			"Warning",
			"Error",
			"AssertSuccess",
			"AssertFailure"
		};

		return names[intl::ScanLogLevel(_lvl) + 1u];
	}

	std::wstring ToWString(LogLevel _lvl) noexcept
	{
		static constexpr const wchar_t* const names[]{
			L"Unknown",
			L"Normal",
			L"Info",
			L"Warning",
			L"Error",
			L"AssertSuccess",
			L"AssertFailure"
		};

		return names[intl::ScanLogLevel(_lvl) + 1u];
	}

#endif

// ##############################################################


// ##############################################################
// #					LOG CHANNEL								#
// ##############################################################

	/**
	*	Log Channel filter class implementation.
	*
	*	Filter channels and sub-channels availability.
	*
	*	ex: "Edo/TEST/Chan" is enabled only if "Edo", "Edo/TEST" and "Edo/TEST/Chan" channels are enabled.
	*/
	class LogChannelFilter
	{
		/// Registered channels.
		std::unordered_map<std::wstring, bool> mChannels;

		bool IsSingleChannelEnabled(const std::wstring& _chanName) const;

	public:
		/**
		*	Whether a channel is currently enabled or not.
		*
		*	A channel is enabled only if all parent channel are enabled.
		*
		*	\param[in] _chanName	Channel name to filter.
		*	\param[in] _offset		Current offset to check (internal use only).
		*/
		bool IsChannelEnabled(const std::wstring& _chanName, size_t _offset = 0u) const;

		/**
		*	Enable/Disable a channel.
		*	Only the channel itself is enabled/disabled (not the parent channels).
		*
		*	\param[in] _chanName	Channel name to enable/disable.
		*	\param[in] _bEnabled	Whether to enable or disable the channel.
		*/
		void SetChannelEnabled(const std::wstring& _chanName, bool _bEnabled);
	};

#if EDO_DEBUG_IMPLEMENTATION

	namespace intl
	{
		static const std::wstring separators = L"./_-\\|";
	}

	bool LogChannelFilter::IsSingleChannelEnabled(const std::wstring& _chanName) const
	{
		auto it = mChannels.find(_chanName);

		return it != mChannels.cend() ? it->second : true;
	}

	bool LogChannelFilter::IsChannelEnabled(const std::wstring& _chanName, size_t _offset) const
	{
		const size_t fIndex = _chanName.find_first_of(intl::separators, _offset);

		if (fIndex == std::wstring::npos)
			return IsSingleChannelEnabled(_chanName);

		return IsSingleChannelEnabled(_chanName.substr(0u, fIndex)) && IsChannelEnabled(_chanName, fIndex + 1);
	}

	void LogChannelFilter::SetChannelEnabled(const std::wstring& _chanName, bool _bEnabled)
	{
		mChannels[_chanName] = _bEnabled;
	}

#endif // EDO_DEBUG_IMPLEMENTATION

// ##############################################################


// ##############################################################
// #						LOG									#
// ##############################################################

	/// Log type implementation.
	class Log
	{
	public:
		std::source_location src;

		/// User string message.
		std::wstring msg = L"Hello, World!";

		/// Output level.
		LogLevel level = LogLevel::Normal;

		/// Output channel name.
		std::wstring chanName = L"Default";

		/// Additional details string.
		std::wstring details;

		/// Frame number.
		uint32_t frameNum = 0u;

		/// backtracing of logging call.
		std::string backtrace;

		/// Date time.
		tm dateTime;

		/// Default constructor.
		Log() = default;

		/**
		*	\brief \e Value Move Constructor.
		*
		*	\param[in] _src			Source location of the Log.
		*	\param[in] _msg			Message of the Log.
		*	\param[in] _level		Level of the Log.
		*	\param[in] _chanName	Channel's name of the Log.
		*	\param[in] _details		Additional details to display.
		*	\param[in] _frameNum	Frame number of the Log.
		*	\param[in] _backtrace	backtracing of logging call.
		*/
		Log(
			std::source_location _src,
			std::wstring _msg = L"Hello, World!",
			LogLevel _level = LogLevel::Normal,
			std::wstring _chanName = L"Default",
			std::wstring _details = L"",
			uint32_t _frameNum = 0u,
			std::string _backtrace = ""
		) noexcept;
	};

#if EDO_DEBUG_IMPLEMENTATION

	namespace intl
	{
		tm LocalTime(const time_t& _inTime)
		{
			tm qTime; // Queried time.

		#if EDO_DEBUG_WIN
			localtime_s(&qTime, &_inTime);
		#else
			localtime_r(&_inTime, &qTime);
		#endif

			return qTime;
		}

		tm TimeNow()
		{
			time_t now = time(nullptr);

			return LocalTime(now);
		}

		std::wstring DateToWString(const tm& _tm)
		{
			std::wstring str =
				L'[' + ToWString(_tm.tm_hour) +
				L':' + ToWString(_tm.tm_min) +
				L':' + ToWString(_tm.tm_sec) + L']';
			
			return str;
		}

		/**
		*	\brief \e Getter of file name from file path.
		*
		*	\param[in] _filePath	Full path to the file.
		*
		*	\returns pointer to the file name in _filePath.
		*/
		const char* FileNameFromPath(const char* _filePath) noexcept
		{
			// Remove characters until last backslash.
			const char* fileName = std::strrchr(_filePath, '\\');

			if (!fileName) // No backslash found.
				fileName = _filePath;
			else
				fileName += 1; // Remove last '\\' found.


			// Remove characters until last slash.
			if (const char* filePathNoSlash = std::strrchr(fileName, '/'))
			{
				// Remove last '/' found.
				fileName = filePathNoSlash + 1;
			}

			return fileName;
		}
	}

	Log::Log(
		std::source_location _src,
		std::wstring _msg,
		LogLevel _level,
		std::wstring _chanName,
		std::wstring _details,
		uint32_t _frameNum,
		std::string _backtrace
	) noexcept :
		src{ std::move(_src) },
		msg{ std::move(_msg) },
		level{ _level },
		chanName{ std::move(_chanName) },
		details{ std::move(_details) },
		frameNum{ _frameNum },
		backtrace{ std::move(_backtrace) },
		dateTime{ intl::TimeNow() }
	{
	}

	/**
	*	\brief ToWString implementation for log.
	*
	*	Convert log to wstring.
	*
	*	\return log as a wstring.
	*/
	std::wstring ToWString(const Log& _log)
	{
		std::wstring str;

		// Output date.
		str += L'[' + ToWString(_log.dateTime.tm_hour) +
			L':' + ToWString(_log.dateTime.tm_min) +
			L':' + ToWString(_log.dateTime.tm_sec) + L']';

		// Output FrameNum.
		str += L'[' + ToWString(_log.frameNum) + L"] ";

		// Output level and channel.
		str += L'{' + ToWString(_log.level) + L" - " + _log.chanName + L'}';

		// Output location.
		str += L'\t' + ToWString(intl::FileNameFromPath(_log.src.file_name()))
			+ L':' + ToWString(_log.src.line()) +
			L" - " + ToWString(_log.src.function_name()) + L'\n';

		// Output message.
		str += L"Msg:\t" + _log.msg + L'\n';

		if (!_log.details.empty())
			str += L"Dets:\t" + _log.details + L'\n';

		if (!_log.backtrace.empty())
			str += L"Backtrace:\t" + ToWString(_log.backtrace) + L'\n';

		return str;
	}

#endif // EDO_DEBUG_IMPLEMENTATION

// ##############################################################

// ##############################################################################################################################


// ##############################################################################################################################
// #													STREAMS																	#
// ##############################################################################################################################

// ##############################################################
// #					ALogStream								#
// ##############################################################

	/// Abstract log stream class.
	class ALogStream
	{
	protected:
		/**
		*	\brief Output a log in stream.
		*
		*	\param[in] _log		Log to output.
		*/
		virtual void Output(const Log& _log) = 0;

	public:
		/// Channel filter used for log in stream.
		LogChannelFilter channelFilter;

		/// Level filter used for log in stream.
		uint8_t levelFlags = static_cast<uint8_t>(LogLevel::Default);

		/// \e Default virtual destructor.
		virtual ~ALogStream() = default;

		/**
		*	\brief Process a log to output in stream.
		*
		*	\param[in] _log		Log to process.
		*	\param[in] _bForce	Should force log process. Default is false.
		*/
		void ProcessLog(const Log& _log, bool _bForce = false);

		/**
		*	\brief Force the stream to flush.
		*/
		virtual void Flush();

		/**
		*	\brief Output log operator.
		*
		*	\param[in] _log		Log to output.
		*
		*	\return this.
		*/
		ALogStream& operator<<(const Log& _log);
	};

#if EDO_DEBUG_IMPLEMENTATION

	void ALogStream::ProcessLog(const Log& _log, bool _bForce)
	{
		const bool bLevelEnabled = levelFlags & static_cast<uint8_t>(_log.level);
		const bool bChannelEnabled = channelFilter.IsChannelEnabled(_log.chanName);

		if (_bForce || (bLevelEnabled && bChannelEnabled))
			Output(_log);
	}

	void ALogStream::Flush()
	{
		/* Implementation in children */
	}

	ALogStream& ALogStream::operator<<(const Log& _log)
	{
		ProcessLog(_log);

		return *this;
	}

#endif // EDO_DEBUG_IMPLEMENTATION

// ##############################################################


// ##############################################################
// #					ConsoleLogStream						#
// ##############################################################

	/**
	*	\brief Console Color enum.
	*
	*	Bright BG bit		BG Color bits		Bright FG bit		FG Color bits
	*		0					000					0					000
	*/
	enum ConsoleColor : uint8_t
	{
		// 4 bits for foreground attributes.

		// 3 bits for foreground color (text).

		/// Default foreground.
		None_FG = 0,

		/// Red foreground.
		Red_FG = 1,

		/// Green foreground.
		Green_FG = 2,

		/// Blue foreground.
		Blue_FG = 3,

		/// Cyan foreground.
		Cyan_FG = 4,

		/// Magenta foreground.
		Magenta_FG = 5,

		/// Yellow foreground.
		Yellow_FG = 6,

		/// Black foreground.
		Black_FG = 7,


		/// 1 bit for bright attribute.
		Bright_FG = 8,


		// 4 bits for background attributes.

		// 3 bits for background color.

		/// Default background.
		None_BG = 0 << 4,

		/// Red background.
		Red_BG = 1 << 4,

		/// Green background.
		Green_BG = 2 << 4,

		/// Blue background.
		Blue_BG = 3 << 4,

		/// Cyan background.
		Cyan_BG = 4 << 4,

		/// Magenta background.
		Magenta_BG = 5 << 4,

		/// Yellow background.
		Yellow_BG = 6 << 4,

		/// White background.
		White_BG = 7 << 4,


		/// 1 bit for Bright attribute.
		Bright_BG = 8 << 4,

		/// Reset console color value.
		Reset = None_FG | None_BG,
	};

	/// Shortcut alias.
	using CslColor = ConsoleColor;

	/**
	*	\brief \e Crossplatform implementation of set color in console.
	*
	*	\param[in] _cslColor	Console color mask.
	*/
	void SetConsoleColor(ConsoleColor _cslColor);


	/**
	*	Console color theme by LogLevel.
	*/
	struct ConsoleColorTheme
	{
		/// Normal level color.
		uint8_t normal = CslColor::Bright_FG;

		/// Info level color.
		uint8_t info = CslColor::Blue_FG | CslColor::Bright_FG;

		/// Warning level color.
		uint8_t warning = CslColor::Yellow_FG;

		/// Error level color.
		uint8_t error = CslColor::Red_FG | CslColor::Bright_FG;

		/// Assert Success level color.
		uint8_t assertSuccess = CslColor::Green_FG | CslColor::Bright_FG;

		/// Assert Failure level color.
		uint8_t assertFailure = CslColor::Magenta_FG | CslColor::Bright_FG;


		/**
		*	\brief convert theme to data type.
		* 
		*	\returns this as uint8_t data.
		*/
		const uint8_t* Data() const;

		/**
		*	\brief Set console color from log level using theme.
		* 
		*	\param[in] _lvl		LogLevel to use for theme.
		*/
		void SetConsoleColorFromLevel(LogLevel _lvl) const;
	};


	/// Console log stream implementation.
	class ConsoleLogStream : public ALogStream
	{
		void Output(const Log& _log) override final;

	public:
		/// Color theme.
		ConsoleColorTheme theme;

		void Flush() override final;
	};

#if EDO_DEBUG_IMPLEMENTATION

	namespace intl
	{
#if EDO_DEBUG_WIN

		/// Windows console handle.
		static HANDLE cslHandle = GetStdHandle(STD_OUTPUT_HANDLE);

#endif // EDO_DEBUG_WIN
	}

	void SetConsoleColor(ConsoleColor _cslColor)
	{
	#if EDO_DEBUG_WIN

		uint8_t attrib = 0u;

		const uint8_t fg = 0x07 & _cslColor; // fg bits only.

		switch (fg)
		{
			case ConsoleColor::None_FG:
				attrib = 7;
				break;
			case ConsoleColor::Red_FG:
				attrib = 4;
				break;
			case ConsoleColor::Green_FG:
				attrib = 2;
				break;
			case ConsoleColor::Blue_FG:
				attrib = 1;
				break;
			case ConsoleColor::Cyan_FG:
				attrib = 3;
				break;
			case ConsoleColor::Magenta_FG:
				attrib = 5;
				break;
			case ConsoleColor::Yellow_FG:
				attrib = 6;
				break;
			case ConsoleColor::Black_FG:
				attrib = 0u;
				break;
			default:
				// TODO: Debug.
				//SA_LOG(L"ConsoleColor foreground bit [" << fg << L"] not supported", Warning, Core);
				attrib = 7;
				break;
		}

		if (_cslColor & ConsoleColor::Bright_FG) // Bright foreground?
			attrib += 8u;


		const uint8_t bg = 0x70 & _cslColor; // bg bits only.

		switch (bg)
		{
			case ConsoleColor::None_BG:
				break;
			case ConsoleColor::Red_BG:
				attrib += 4u << 4u;
				break;
			case ConsoleColor::Green_BG:
				attrib += 2u << 4u;
				break;
			case ConsoleColor::Blue_BG:
				attrib += 1u << 4u;
				break;
			case ConsoleColor::Cyan_BG:
				attrib += 3u << 4u;
				break;
			case ConsoleColor::Magenta_BG:
				attrib += 5u << 4u;
				break;
			case ConsoleColor::Yellow_BG:
				attrib += 6u << 4u;
				break;
			case ConsoleColor::White_BG:
				attrib += 7u << 4u;
				break;
			default:
				// TODO: Debug.
				//SA_LOG(L"ConsoleColor background bit [" << bg << L"] not supported", Warning, Core);
				break;
		}

		if (_cslColor & ConsoleColor::Bright_BG) // Bright background?
			attrib += 8u << 4u;


		SetConsoleTextAttribute(intl::cslHandle, attrib);

	#else // EDO_DEBUG_WIN

		std::string attrib = "\033[";
		const uint8_t fg = 0x07 & _cslColor; // fg bits only.

		// Bright? Unix share fg and bg brightness.
		attrib += _cslColor & (ConsoleColor::Bright_FG | ConsoleColor::Bright_BG) ? "1;" : "0;";

		switch (fg)
		{
			case ConsoleColor::None_FG:
				attrib += "0";
				break;
			case ConsoleColor::Red_FG:
				attrib += "31";
				break;
			case ConsoleColor::Green_FG:
				attrib += "32";
				break;
			case ConsoleColor::Blue_FG:
				attrib += "34";
				break;
			case ConsoleColor::Cyan_FG:
				attrib += "36";
				break;
			case ConsoleColor::Magenta_FG:
				attrib += "35";
				break;
			case ConsoleColor::Yellow_FG:
				attrib += "33";
				break;
			case ConsoleColor::Black_FG:
				attrib += "30";
				break;
			default:
				// TODO: Debug.
				//SA_LOG(L"ConsoleColor foreground bit [" << fg << L"] not supported", Warning, Core);
				break;
		}

		uint8_t bg = 0x70 & _cslColor; // bg bits only.

		switch (bg)
		{
			case ConsoleColor::None_BG:
				break;
			case ConsoleColor::Red_BG:
				attrib += ";41";
				break;
			case ConsoleColor::Green_BG:
				attrib += ";42";
				break;
			case ConsoleColor::Blue_BG:
				attrib += ";44";
				break;
			case ConsoleColor::Cyan_BG:
				attrib += ";46";
				break;
			case ConsoleColor::Magenta_BG:
				attrib += ";45";
				break;
			case ConsoleColor::Yellow_BG:
				attrib += ";43";
				break;
			case ConsoleColor::White_BG:
				attrib += ";47";
				break;
			default:
				// TODO: Debug.
				//SA_LOG(L"ConsoleColor background bit [" << bg << L"] not supported", Warning, Core);
				break;
		}

		attrib += "m";

		std::cout << attrib;

	#endif // EDO_DEBUG_WIN
	}


	const uint8_t* ConsoleColorTheme::Data() const
	{
		return &normal;
	}

	void ConsoleColorTheme::SetConsoleColorFromLevel(LogLevel _lvl) const
	{
		const uint8_t* const data = Data();

		const CslColor color = static_cast<CslColor>(data[intl::ScanLogLevel(_lvl)]);

		edo::SetConsoleColor(color);
	}


	void ConsoleLogStream::Flush()
	{
#if EDO_DEBUG_WIN
		FlushConsoleInputBuffer(intl::cslHandle);
#else
		std::wcout.flush();
#endif
	}

	void ConsoleLogStream::Output(const Log& _log)
	{
		theme.SetConsoleColorFromLevel(_log.level);

#if EDO_DEBUG_WIN
		std::wstring msg = ToWString(_log) + L'\n';
		WriteConsoleW(intl::cslHandle, msg.data(), static_cast<DWORD>(msg.size()), 0, NULL);
#else
		std::wcout << ToWString(_log) << L'\n';
#endif

		edo::SetConsoleColor(CslColor::Reset);
	}

#endif // EDO_DEBUG_IMPLEMENTATION

// ##############################################################


// ##############################################################
// #					FileLogStream							#
// ##############################################################

	/// Log file stream type.
	class FileLogStream : public ALogStream
	{
	protected:
		/// Handled file stream.
		std::wofstream mHandle;

		/**
		*	\brief Create log and log backup files.
		*
		*	\param[in] _fileFullPath	Name and path of the log file.
		*/
		void CreateLogFile(const std::string& _fileFullPath);


		void Output(const Log& _log) override final;

	public:
		/**
		*	\e Value Constructor
		*
		*	\param[in] _fileFullPath	Name and path of the file.
		*/
		FileLogStream(const std::string& _fileFullPath = "Logs/log.txt") noexcept;

		/**
		*	\e Destructor. Close the file stream.
		*/
		~FileLogStream() noexcept;


		void Flush() override final;
	};

#if EDO_DEBUG_IMPLEMENTATION

	FileLogStream::FileLogStream(const std::string& _fileFullPath) noexcept
	{
		CreateLogFile(_fileFullPath);
	}

	FileLogStream::~FileLogStream() noexcept
	{
		mHandle.close();
	}

	void FileLogStream::CreateLogFile(const std::string& _fileFullPath)
	{
		const size_t pathIndex = _fileFullPath.find_last_of("/\\");

		std::string filePath;
		std::string fileName;

		// Should create directory?
		if (pathIndex != std::string::npos)
		{
			filePath = _fileFullPath.substr(0u, pathIndex);
			fileName = _fileFullPath.substr(pathIndex);

			std::filesystem::create_directories(filePath);
		}
		else
			fileName = _fileFullPath;


		// Has extension?
		std::string fileExt;
		const size_t extIndex = _fileFullPath.rfind('.');

		if (extIndex != std::string::npos)
		{
			fileExt = _fileFullPath.substr(extIndex);
			fileName = fileName.substr(0u, extIndex);
		}


		// Log file already exists? Create backup.
		if (std::filesystem::exists(_fileFullPath))
		{
			// Query old file time info.
			struct stat backupStat;
			stat(_fileFullPath.c_str(), &backupStat);

			const tm qTime = intl::LocalTime(backupStat.st_mtime);

			std::filesystem::rename(_fileFullPath.c_str(), (filePath + fileName + "_backup-" + ToString(qTime) + fileExt).c_str());
		}

		mHandle.open(_fileFullPath, std::ios::out);
	}


	void FileLogStream::Flush()
	{
		mHandle.flush();
	}

	void FileLogStream::Output(const Log& _log)
	{
		mHandle << ToWString(_log) << std::endl;
	}

#endif // EDO_DEBUG_IMPLEMENTATION

// ##############################################################

// ##############################################################################################################################


// ##############################################################################################################################
// #													LOGGER																	#
// ##############################################################################################################################

// ##############################################################
// #					ALoggerBase								#
// ##############################################################

	/**
	*	\brief Logger base class implementation.
	*/
	class ALoggerBase
	{
	protected:

//{ Streams

		/// Registered output streams.
		std::list<ALogStream*> mStreams;

		/**
		*	\brief Process log to output.
		* 
		*	\param[in] _log		Log to process.
		*	\param[in] _bForce	Should force log process. Default is false.
		*/
		virtual void ProcessLog(const edo::Log& _log, bool _bForce = false);

		/**
		*	\brief Register a stream to output.
		* 
		*	\param[in] _stream	Stream to register.
		*/
		virtual void RegisterStream(ALogStream* _stream);

		/**
		*	\brief Unregister a stream from output.
		*
		*	\param[in] _stream	Stream to unregister.
		*
		*	\return true on success.
		*/
		virtual bool UnregisterStream(ALogStream* _stream);

//}

	public:
		/**
		*	\brief Destructor
		*	Destroy all created log streams.
		*/
		virtual ~ALoggerBase();

		/**
		*	\brief Push a new log in logger.
		* 
		*	\param[in] _log		Log to push.
		*/
		virtual void Log(edo::Log _log);

		/**
		*	\brief Process exception.
		*
		*	Log assertion on success, otherwise throw exception.
		*	Use EDO_ASSERT as helper call.
		*
		*	\param[in] _exc		exception to process.
		*/
		void Assert(edo::Log _exc);


//{ Streams

		/**
		*	\brief Create a new stream to output in.
		* 
		*	\tparam StreamT 	Type of stream to create.
		*	\tparam Args...		Argument variadic types to construct stream.
		*	\param[in] _args	Arguments to construct stream.
		*
		*	\return Newly created stream.
		*/
		template <typename StreamT, typename... Args>
		StreamT& CreateSteam(Args&&... _args)
		{
			StreamT* const stream = new StreamT(std::forward<Args>(_args)...);

			RegisterStream(stream);

			return *stream;
		}

		/**
		 * \brief Destroy a previously created stream.
		 * 
		 * \tparam StreamT 	Type of stream to destroy.
		 * \param _stream 	Stream variable to destroy.
		 * \param _bFlush 	Should flush stream before destroy.
		 * 
		 * \return true on destroy success.
		 */
		template <typename StreamT>
		bool DestroyStream(StreamT& _stream, bool _bFlush = true)
		{
			StreamT* const streamPtr = &_stream;

			const bool bUnregisted = UnregisterSteam(streamPtr);

			if (bUnregisted)
			{
				if (_bFlush)
					streamPtr->Flush();

				delete streamPtr;
			}

			return bUnregisted;
		}


		/**
		*	Destroy all streams.
		* 
		*	\param _bFlush 	Should flush stream before destroy.
		*/
		virtual void ClearStreams(bool _bFlush = true);


		/**
		*	\brief Force logger to flush all streams.
		*/
		virtual void Flush();


		/**
		*	\brief \e Enable \b LogLevel for all registered streams.
		* 
		*	\param[in] _level		Level to enable.
		*/
		virtual void EnableLevel(LogLevel _level);

		/**
		*	\brief \e Disable \b LogLevel for all registered streams.
		*
		*	\param[in] _level		Level to disable.
		*/
		virtual void DisableLevel(LogLevel _level);


		/**
		*	\brief \e Enable \b LogChannel for all registered streams.
		* 
		*	\param[in] _channel		Channel to enable.
		*/
		virtual void EnableChannel(const std::wstring& _channel);

		/**
		*	\brief \e Disable \b LogChannel for all registered streams.
		*
		*	\param[in] _channel		Channel to disable.
		*/
		virtual void DisableChannel(const std::wstring& _channel);

//}


//{ Frame Num

		/// Increment current registered frame number.
		virtual void IncrementFrameNum() = 0;

		/// Get current registered frame number.
		virtual uint32_t GetFrameNum() const = 0;

//}
	};

#if EDO_DEBUG_IMPLEMENTATION

	ALoggerBase::~ALoggerBase()
	{
		ClearStreams();
	}

	void ALoggerBase::Log(edo::Log _log)
	{
		ProcessLog(_log);
	}

	void ALoggerBase::Assert(edo::Log _exc)
	{
		if (_exc.level == LogLevel::AssertFailure)
		{
			Flush();

			// Force instant process.
			ProcessLog(_exc, true);

			throw std::move(_exc);
		}
		else
		{
			// Simple log.
			Log(std::move(_exc));
		}
	}

//{ Streams

	void ALoggerBase::ProcessLog(const edo::Log& _log, bool _bForce)
	{
		for (auto it = mStreams.begin(); it != mStreams.end(); ++it)
			(*it)->ProcessLog(_log, _bForce);
	}


	void ALoggerBase::RegisterStream(ALogStream* _stream)
	{
		mStreams.push_back(_stream);
	}

	bool ALoggerBase::UnregisterStream(ALogStream* _stream)
	{
		for (auto it = mStreams.begin(); it != mStreams.end(); ++it)
		{
			if (*it == _stream)
			{
				mStreams.erase(it);
				return true;
			}
		}

		return false;
	}


	void ALoggerBase::ClearStreams(bool _bFlush)
	{
		for (auto it = mStreams.begin(); it != mStreams.end(); ++it)
		{
			if (_bFlush)
				(*it)->Flush();
			
			delete *it;
		}

		mStreams.clear();
	}


	void ALoggerBase::Flush()
	{
		for (auto it = mStreams.begin(); it != mStreams.end(); ++it)
			(*it)->Flush();
	}


	void ALoggerBase::EnableLevel(LogLevel _level)
	{
		for (auto it = mStreams.begin(); it != mStreams.end(); ++it)
			(*it)->levelFlags |= static_cast<uint8_t>(_level);
	}

	void ALoggerBase::DisableLevel(LogLevel _level)
	{
		for (auto it = mStreams.begin(); it != mStreams.end(); ++it)
			(*it)->levelFlags &= ~static_cast<uint8_t>(_level);
	}


	void ALoggerBase::EnableChannel(const std::wstring& _channel)
	{
		for (auto it = mStreams.begin(); it != mStreams.end(); ++it)
			(*it)->channelFilter.SetChannelEnabled(_channel, true);
	}

	void ALoggerBase::DisableChannel(const std::wstring& _channel)
	{
		for (auto it = mStreams.begin(); it != mStreams.end(); ++it)
			(*it)->channelFilter.SetChannelEnabled(_channel, false);
	}

//}

#endif // EDO_DEBUG_IMPLEMENTATION

// ##############################################################


// ##############################################################
// #					Logger									#
// ##############################################################

	/**
	*	\brief Basic Logger class implementation.
	*
	*	Non-thread-safe logging.
	*/
	class Logger : public ALoggerBase
	{
		/**
		* \brief Current registered frame number.
		* Use IncrementFrameNum() or SA_LOG_END_OF_FRAME() at the end of the frame to track frame number.
		*/
		uint32_t mFrameNum = 0u;

	public:

//{ Frame Num

		void IncrementFrameNum() override final;

		uint32_t GetFrameNum() const override final;

//}
	};

#if EDO_DEBUG_IMPLEMENTATION

	void Logger::IncrementFrameNum()
	{
		mFrameNum = (mFrameNum + 1) % 10000;
	}

	uint32_t Logger::GetFrameNum() const
	{
		return mFrameNum;
	}

#endif // EDO_DEBUG_IMPLEMENTATION

// ##############################################################


// ##############################################################
// #					Logger-Thread							#
// ##############################################################

	/**
	*	\brief Multithread logger class.
	* 
	*	Create one thread for log output.
	*	Push logs in thread-safe queue.
	*/
	class LoggerThread : public ALoggerBase
	{
	};

// ##############################################################


// ##############################################################
// #						Instance							#
// ##############################################################

	/// Global Debug namespace
	namespace Debug
	{
		/// Logger instance.
		extern ALoggerBase* logger;

		/// Simple logger callback.
		extern void (*logCB)(edo::Log);


		/**
		* \brief Initialize default logger for single-thread use.
		* Console color and file output.
		*/
		void InitDefaultLogger();

		/**
		* \brief Initialize default logger for multi-thread use.
		* Console color and file output.
		*/
		void InitDefaultLoggerThread();


#if EDO_DEBUG_IMPLEMENTATION

		namespace intl
		{
			void DefaultLogCallback(edo::Log _log)
			{
				std::wcout << edo::ToWString(_log) << std::endl;
			}
		}

		ALoggerBase* logger = nullptr;
		void (*logCB)(edo::Log) = intl::DefaultLogCallback;

		void InitDefaultLogger()
		{
			static Logger defaultLogger;

			defaultLogger.CreateSteam<ConsoleLogStream>();
			defaultLogger.CreateSteam<FileLogStream>();

			edo::Debug::logger = &defaultLogger;
		}

		void InitDefaultLoggerThread()
		{
			// TODO

			//static LoggerThread defaultLoggerThread;

			//defaultLoggerThread.CreateSteam<ConsoleLogStream>();
			//defaultLoggerThread.CreateSteam<FileLogStream>();

			//edo::Debug::logger = &defaultLoggerThread;
		}

#endif // EDO_DEBUG_IMPLEMENTATION
	}

// ##############################################################


// ##############################################################
// #						MACROs								#
// ##############################################################

	/// Convert any _param into a const char8* (Stringification).
	#define EDO_STR(_param) # _param

	/// Convert a string _param into a const wchar*
	#define EDO_WIDE(_param) L"" _param

	/// Convert any _param into a const wchar* (Wide Stringification)
	#define EDO_WSTR(_param) EDO_WIDE(EDO_STR(_param))

	/**
	 * Optional macro argument parentheses: remove "only if" parentheses.
	 * 
	 * Sources:
	 * https://stackoverflow.com/a/62984543
	 * https://www.mikeash.com/pyblog/friday-qa-2015-03-20-preprocessor-abuse-and-optional-parentheses.html
	*/
	#define __EDO_EXTRACT(...) __EDO_EXTRACT __VA_ARGS__
	#define __EDO_NOTHING__EDO_EXTRACT
	#define __EDO_PASTE(_x, ...) _x ## __VA_ARGS__
	#define __EDO_EVAL_PASTE(_x, ...) __EDO_PASTE(_x, __VA_ARGS__)
	#define __EDO_UNPARENT(_x) __EDO_EVAL_PASTE(__EDO_NOTHING, __EDO_EXTRACT _x)

	#define __EDO_LOG_FRAME_NUM\
		edo::Debug::logger ? edo::Debug::logger->GetFrameNum() : 0u

	#define __EDO_LOGGER(_log)\
		if (edo::Debug::logger)\
			edo::Debug::logger->Log(_log);\
		else if (edo::Debug::logCB)\
			edo::Debug::logCB(_log);\
		else\
			std::cerr << "Try logging with invalid logger instance or callback! Initialize edo::Debug::logger or edo::Debug::logCB." << std::endl;

	#define __EDO_CREATE_LOG(_str, _lvl, _chan, _dets) edo::Log(\
		std::source_location::current(),\
		edo::StringFormat(__EDO_UNPARENT(_str)),\
		edo::LogLevel::_lvl,\
		EDO_WSTR(_chan),\
		edo::StringFormat(__EDO_UNPARENT(_dets)),\
		__EDO_LOG_FRAME_NUM,\
		std::string()\
	)

	// TODO: Add backtrace.

	#define __EDO_LOG_SELECTOR(_1, _2, _3, _4, _5, _name, ...) _name

	#define __EDO_LOG4(_str, _lvl, _chan, _dets)				__EDO_LOGGER(__EDO_CREATE_LOG(_str, _lvl, _chan, _dets));
	#define __EDO_LOG5(_str, _lvl, _chan, _dets, _postCmd)		{ __EDO_LOG4(_str, _lvl, _chan, _dets) _postCmd; }
	#define __EDO_LOG3(_str, _lvl, _chan)						__EDO_LOG4(_str, _lvl, _chan, L"")
	#define __EDO_LOG2(_str, _lvl)								__EDO_LOG3(_str, _lvl, Default)
	#define __EDO_LOG1(_str)									__EDO_LOG2(_str, Normal)

	#define __EDO_COND_LOG(_pred, _lvl, ...)		if(!(_pred)) EDO_LOG(L"{ " EDO_WSTR(_pred) " }\tevaluated to false!", _lvl, ##__VA_ARGS__)


	#define __EDO_ASSERT(_log)\
		if (edo::Debug::logger)\
			edo::Debug::logger->Assert(_log);\
		else if (edo::Debug::logCB)\
			edo::Debug::logCB(_log);\
		else\
			std::cerr << "Try logging with invalid logger instance or callback! Initialize edo::Debug::logger or edo::Debug::logCB." << std::endl;

	#define __EDO_ASSERT_SELECTOR(_1, _2, _name, ...) _name

	#define __EDO_ASSERT4(_str, _lvl, _chan, _dets){\
		auto exc = __EDO_CREATE_LOG(_str, _lvl, _chan, _dets);\
		if (exc.level != edo::LogLevel::AssertFailure) { __EDO_ASSERT(std::move(exc)); }\
		else { __EDO_ASSERT(exc); throw exc; }\
	}
	#define __EDO_ASSERT3(_str, _lvl, _chan)	__EDO_ASSERT4(_str, _lvl, _chan, L"")
	#define __EDO_ASSERT2(_str, _lvl)			__EDO_ASSERT3(_str, _lvl, Default)

#if EDO_DEBUG

	/**
	*	\def EDO_LOG_END_OF_FRAME()
	*
	*	\brief Edo Log end of frame macro.
	*
	*	Helper macro to track frame number used for logging.
	*/
	#define EDO_LOG_END_OF_FRAME() { if(edo::Debug::logger) edo::Debug::logger->IncrementFrameNum(); }

	/**
	*	\def EDO_LOG((_str, _args), _lvl, _chan, _dets)
	*
	*	\brief Edo Log macro.
	*
	*	Helper macro to use Debug::Log.
	*
	*	\param[in] _str		String message of the log. Parentheses are optionnal for single string or object.
	*	\param[in] _args	Arguments to insert in string using %<num>. Must add parentheses surrounding: (_str, _args).
	*	\param[in] _lvl		Level of the log (optional).
	*	\param[in] _chan	Channel of the log (optional).
	*	\param[in] _dets	Details string of the log (optional).
	*/
	#define EDO_LOG(...) { __EDO_LOG_SELECTOR(__VA_ARGS__, __EDO_LOG5, __EDO_LOG4, __EDO_LOG3, __EDO_LOG2, __EDO_LOG1)(__VA_ARGS__) }

	/**
	*	\def EDO_WARN(_pred, _chan, _dets, _postCmd)
	*
	*	\brief Edo Log "warning if" macro.
	*
	*	Helper macro to use conditionnal Debug::Log warning.
	*
	*	\param[in] _pred	predicate of the Log. Output warnings on false.
	*	\param[in] _chan	Channel of the log.
	*	\param[in] _dets	Details string of the log (optional).
	*	\param[in] _postCmd	Post-log command on true predicate, usually for return value (optional).
	*/
	#define EDO_WARN(_pred, ...) { __EDO_COND_LOG(_pred, Warning, ##__VA_ARGS__) }

	/**
	*	\def EDO_ERROR(_pred, _chan, _dets, _postCmd)
	*
	*	\brief Edo Log "error if" macro.
	*
	*	Helper macro to use conditionnal Debug::Log error.
	*
	*	\param[in] _pred	predicate of the Log. Output error on false.
	*	\param[in] _chan	Channel of the log (optional).
	*	\param[in] _dets	Details string of the log (optional).
	*	\param[in] _postCmd	Post-log command on true predicate, usually for return value (optional).
	*/
	#define EDO_ERROR(_pred, ...) { __EDO_COND_LOG(_pred, Error, ##__VA_ARGS__) }

	/**
	*	\def EDO_ASSERT(_pred, _chan, _dets, _postCmd)
	*
	*	\brief Edo Log "assert if" macro.
	*
	*	Helper macro to use conditionnal Debug::Log assert.
	*
	*	\param[in] _pred	predicate of the Log. Output AssertFailure on false and AssertSuccess on true.
	*	\param[in] _chan	Channel of the log (optional).
	*	\param[in] _dets	Details string of the log (optional).
	*	\param[in] _postCmd	Post-log command on true predicate, usually for return value (optional).
	*/
	#define EDO_ASSERT(_pred, ...)\
	{\
		auto bPred = (_pred);\
		if (bPred) { __EDO_ASSERT_SELECTOR(__VA_ARGS__, __EDO_ASSERT4, __EDO_ASSERT3, __EDO_ASSERT2)(L"{ " EDO_WSTR(_pred) " }\tevaluated to true!", AssertSuccess, ##__VA_ARGS__) }\
		else { __EDO_ASSERT_SELECTOR(__VA_ARGS__, __EDO_ASSERT4, __EDO_ASSERT3, __EDO_ASSERT2)(L"{ " EDO_WSTR(_pred) " }\tevaluated to false!", AssertFailure, ##__VA_ARGS__) }\
	}

#else

	#define EDO_LOG_END_OF_FRAME() {}

	#define EDO_LOG(...) {}

	#define EDO_WARN(...) {}

	#define EDO_ERROR(...) {}

	#define EDO_ASSERT(...) {}

#endif

// ##############################################################

// ##############################################################################################################################
}

#endif // EDO_SH_DEBUG_GUARD
