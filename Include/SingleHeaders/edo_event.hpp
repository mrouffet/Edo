// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_SH_EVENT_GUARD
#define EDO_SH_EVENT_GUARD

#include <utility>
#include <type_traits>

namespace edo
{
// ##############################################################
// #					FUNCTION								#
// ##############################################################

	namespace intl
	{
		/**
		*	\brief Interface for abstract function handling.
		*
		*	Interface class to store template child class as abstract.
		*/
		template <typename R, typename... Args>
		struct IFuncHandle
		{
			/**
			*	\brief default virtual destructor.
			*	Ensure correct child class destruction on delete.
			*/
			virtual ~IFuncHandle() = default;

			/**
			*	\brief \b Duplicate child data (used for copy operations).
			*
			*	\return new data duplicated.
			*/
			virtual IFuncHandle* Duplicate() const = 0;

			/**
			*	\brief \b Compare child data class
			*
			*	\param[in] _other	member to compare to.
			*
			*	\return true on equality.
			*/
			virtual bool Compare(const IFuncHandle* _other) const = 0;

			/**
			*	\brief \b Execute typed implementation.
			*
			*	return Bound function result value.
			*/
			virtual R Execute(Args... _args) = 0;

			/**
			* \brief \b Store result internally if memory was provided
			* 
			*	return Store operation success.
			*/
			virtual bool StoreResult(void* _result)
			{
				(void)_result;
				return false;
			}
		};

		/**
		*	\brief Struct for <b>typed</b> function handling.
		*
		*	\tparam C		Caller type of function's declaration.
		*	\tparam R		Return type of function's declaration.
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename R, typename... Args>
		struct FuncHandle : public IFuncHandle<R, Args...>
		{
			/// Static Function ptr handle.
			R(*func)(Args...) = nullptr;


			/**
			*	\brief Default value constructor.
			*
			*	\param[in] _func	Static function to call.
			*/
			FuncHandle(R(*_func)(Args...)) noexcept :
				func{ _func }
			{
			}

			IFuncHandle<R, Args...>* Duplicate() const override final
			{
				return new FuncHandle(func);
			}

			bool Compare(const IFuncHandle<R, Args...>* _other) const override
			{
				const FuncHandle* oFuncH = static_cast<const FuncHandle*>(_other);

				return func == oFuncH->func;
			}

			R Execute(Args... _args) override final
			{
				//SA_ASSERT((Nullptr, _func), SA.Event.FuncHandle);

				return (*func)(std::forward<Args>(_args)...);
			}
		};

		/**
		*	\brief Struct for <b>typed</b> member function handling.
		*
		*	\tparam C		Caller type of function's declaration.
		*	\tparam R		Return type of function's declaration.
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename C, typename R, typename... Args>
		struct MemFuncHandle : public IFuncHandle<R, Args...>
		{
			/// Member Function ptr handle. Stored first for valid abstract comparison.
			R(C::* func)(Args...) = nullptr;

			/// Caller ptr handle.
			C* caller = nullptr;


			/**
			*	\brief Default value constructor.
			*
			*	\param[in] _caller	Caller of the member function.
			*	\param[in] _func	Member function to call.
			*/
			MemFuncHandle(C* _caller, R(C::* _func)(Args...)) noexcept :
				func{ _func },
				caller{ _caller }
			{
			}

			IFuncHandle<R, Args...>* Duplicate() const override final
			{
				return new MemFuncHandle(caller, func);
			}

			bool Compare(const IFuncHandle<R, Args...>* _other) const override
			{
				const MemFuncHandle* oFuncH = static_cast<const MemFuncHandle*>(_other);

				return func == oFuncH->func && caller == oFuncH->caller;
			}

			R Execute(Args... _args) override final
			{
				//SA_ASSERT((Nullptr, _caller), SA.Event.MemFuncHandle);
				//SA_ASSERT((Nullptr, _func), SA.Event.MemFuncHandle);

				return (caller->*func)(std::forward<Args>(_args)...);
			}
		};
	}


	/**
	*	\brief \b Function type implementation.
	* 
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class Function
	{
		/// Abstract function handle.
		intl::IFuncHandle<R, Args...>* mHandle = nullptr;

	public:

//{ Constructors

		/// Default constructor.
		Function() = default;

		/**
		*	\e Value constructor with static function.
		* 
		*	\param[in] _func	Static function to bind.
		*/
		Function(R(*_func)(Args...)) :
			mHandle{ new intl::FuncHandle<R, Args...>(_func) }
		{
		}

		/**
		*	\e Value constructor with member function.
		*
		*	\tparam C			Caller type.
		*	\param[in] _caller	Object caller of member function.
		*	\param[in] _func	Member function to bind.
		*/
		template <typename C>
		Function(C* _caller, R(C::* _func)(Args...)) :
			mHandle{ new intl::MemFuncHandle<C, R, Args...>(_caller, _func) }
		{
		}

		/**
		*	\e Move constructor.
		*	Steal function handle (no additional memory allocation).
		*
		*	\param[in] _other	Other handle to move.
		*/
		Function(Function&& _other) noexcept :
			mHandle{ _other.mHandle }
		{
			_other.mHandle = nullptr;
		}

		/**
		*	\e Copy constructor.
		*	Additional memory allocation on member function copy.
		*
		*	\param[in] _other	Other handle to copy.
		*/
		Function(const Function& _other) noexcept :
			mHandle{ _other.mHandle ? _other.mHandle->Duplicate() : nullptr }
		{
		}

		/// Destructor (free memory).
		~Function()
		{
			Clear();
		}
//}


//{ Equals

		/**
		*	\brief Check whether this function handle is <b>empty</b> (no function bound).
		*
		*	\returns true if empty.
		*/
		bool IsEmpty() const noexcept
		{
			return !mHandle;
		}

		/**
		*	\brief !IsEmpty bool operator.
		* 
		*	\return true if non empty.
		*/
		operator bool() const
		{
			return mHandle;
		}


		/**
		*	\brief \e Compare 2 function handle.
		*
		*	\param[in] _other		Other function to compare to.
		*
		*	\return Whether this and _other are equal.
		*/
		bool Equals(const Function& _other) const
		{
			if (mHandle)
			{
				if (_other.mHandle)
				{
					return mHandle->Compare(_other.mHandle);
				}
			}
			else if (!_other.mHandle)
			{
				// Both nullptr.
				return true;
			}
			
			return false;
		}

		/**
		*	\brief \e Compare 2 function handle equality.
		*
		*	\param[in] _rhs		Other function to compare to.
		*
		*	\return Whether this and _other are equal.
		*/
		bool operator==(const Function& _rhs) const
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 function handle inequality.
		*
		*	\param[in] _rhs		Other function to compare to.
		*
		*	\return Whether this and _other are non-equal.
		*/
		bool operator!=(const Function& _rhs) const
		{
			return !(*this == _rhs);
		}

//}


//{ Set

		/**
		*	\brief Set (assignation) new <b>static function</b> to bind.
		*	Free previous allocated memory.
		* 
		*	\param[in] _func	New static function to bind.
		*/
		void Set(R(*_func)(Args...))
		{
			Clear();

			mHandle = new intl::FuncHandle(_func);
		}
		
		/**
		*	\brief Set (assignation) new <b>member function</b> to bind.
		*	Free previous allocated memory.
		* 
		*	\tparam C			Caller type.
		*	\param[in] _caller	New object caller of member function.
		*	\param[in] _func	New member function to bind.
		*/
		template <typename C>
		void Set(C* _caller, R(C::* _func)(Args...))
		{
			Clear();

			mHandle = new intl::MemFuncHandle(_caller, _func);
		}


		/**
		*	\brief Move operator
		*	Free previous allocated memory.
		*	Steal function handle (no additional memory allocation).
		*
		*	\param[in] _rhs		Function handle to move.
		* 
		*	\return this.
		*/
		Function& operator=(Function&& _rhs) noexcept
		{
			Clear();

			mHandle = _rhs.mHandle;
			_rhs.mHandle = nullptr;

			return *this;
		}

		/**
		*	\brief Copy operator
		*	Free previous allocated memory.
		*	Additional memory allocation on member function copy.
		* 
		*	\param[in] _rhs		Function handle to move.
		* 
		*	\return this.
		*/
		Function& operator=(const Function& _rhs) noexcept
		{
			Clear();

			if (_rhs.mHandle)
			{
				mHandle = _rhs.mHandle->Duplicate();
			}

			return *this;
		}

		/**
		*	\e Value assignation with static function.
		*	Free previous allocated memory.
		*
		*	\param[in] _func	Static function to bind.
		*
		*	\return this
		*/
		Function& operator=(R(*_func)(Args...)) noexcept
		{
			Set(_func);

			return *this;
		}

		//template <typename C>
		//Function& operator=(C* _caller, R(C::* _func)(Args...));

//}


//{ Clear

		/**
		*	\brief <b>Clear</b> bound function.
		*	Free allocated memory.
		*/
		void Clear()
		{
			if (mHandle)
			{
				delete mHandle;
				mHandle = nullptr;
			}
		}

		/**
		*	\brief <b>Clear</b> bound function.
		*	Free allocated memory.
		* 
		*	\return this 
		*/
		Function& operator=(std::nullptr_t)
		{
			Clear();

			return *this;
		}

//}


//{ Execute

		/**
		*	\brief \b Execute bound function with args.
		* 
		*	\param[in] _args	Argument to forward to bound function.
		* 
		*	\return Bound function result value.
		*/
		R Execute(Args... _args) const
		{
			//SA_ERROR(mHandle)

			if (mHandle)
			{
				return mHandle->Execute(std::forward<Args>(_args)...);
			}

			return R();
		}


		/**
		*	\brief \b Execute bound function with args operator.
		* 
		*	\param[in] _args	Argument to forward to bound function.
		* 
		*	\return Bound function result value.
		*/
		R operator()(Args... _args) const
		{
			return Execute(std::forward<Args>(_args)...);
		}

//}
	};


	/**
	*	\brief Template specialization for R(Args...) deduction.
	* 
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class Function<R(Args...)> : public Function<R, Args...>
	{
	public:
		using Function<R, Args...>::Function;
		using Function<R, Args...>::operator=;
	};

// ##############################################################


// ##############################################################
// #					PACKED FUNCTION							#
// ##############################################################

	/**
	*	\brief <b>Packed Function</b> type implementation.
	*
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class PackedFunction : private Function<R, Args...>
	{
		std::tuple<Args...> mArgs;

	public:

//{ Constructors

		/// Default constructor.
		PackedFunction() = default;

		/**
		*	\e Value constructor with static function.
		*
		*	\param[in] _func	Static function to bind.
		*	\param[in] _args	Args to pack.
		*/
		PackedFunction(R(*_func)(Args...), Args... _args) noexcept :
			Function<R, Args...>(_func),
			mArgs{ std::forward<Args>(_args)... }
		{
		}

		/**
		*	\e Value constructor with member function.
		*
		*	\tparam C			Caller type.
		* 
		*	\param[in] _caller	Object caller of member function.
		*	\param[in] _func	Member function to bind.
		*	\param[in] _args	Args to pack.
		*/
		template <typename C>
		PackedFunction(C* _caller, R(C::* _func)(Args...), Args... _args) :
			Function<R, Args...>(_caller, _func),
			mArgs{ std::forward<Args>(_args)... }
		{
		}


		/**
		*	\e Move constructor.
		*	Steal function handle (no additional memory allocation).
		*
		*	\param[in] _other	Other handle to move.
		*/
		PackedFunction(PackedFunction&& _other) noexcept :
			Function<R, Args...>(std::move(_other)),
			mArgs{ std::move(_other.mArgs) }
		{
		}

		/**
		*	\e Copy constructor.
		*	Additional memory allocation on member function copy.
		*
		*	\param[in] _other	Other handle to copy.
		*/
		PackedFunction(const PackedFunction& _other) noexcept :
			Function<R, Args...>(_other),
			mArgs{ _other.mArgs }
		{
		}

//}


//{ Equals

		using Function<R, Args...>::IsEmpty;
		using Function<R, Args...>::operator bool;


		/**
		*	\brief \e Compare 2 function handle.
		*
		*	\param[in] _other		Other function to compare to.
		*
		*	\return Whether this and _other are equal.
		*/
		bool Equals(const PackedFunction& _other) const
		{
			return Function<R, Args...>::Equals(_other) && mArgs == _other.mArgs;
		}

		/**
		*	\brief \e Compare 2 function handle equality.
		*
		*	\param[in] _rhs		Other function to compare to.
		*
		*	\return Whether this and _other are equal.
		*/
		bool operator==(const PackedFunction& _rhs) const
		{
			return Equals(_rhs);
		}


		/**
		*	\brief \e Compare 2 function handle inequality.
		*
		*	\param[in] _rhs		Other function to compare to.
		*
		*	\return Whether this and _other are non-equal.
		*/
		bool operator!=(const PackedFunction& _rhs) const
		{
			return !(*this == _rhs);
		}

//}


//{ Set

		using Function<R, Args...>::Clear;

		/**
		*	\brief Set (assignation) new <b>static function</b> to bind.
		*	Free previous allocated memory.
		*
		*	\param[in] _func	New static function to bind.
		*	\param[in] _args	Args to pack.
		*/
		void Set(R(*_func)(Args...), Args... _args)
		{
			Function<R, Args...>::Set(_func);
			mArgs = std::tuple<Args...>{ std::forward<Args>(_args)... };
		}

		/**
		*	\brief Set (assignation) new <b>member function</b> to bind.
		*	Free previous allocated memory.
		*
		*	\tparam C			Caller type.
		*	\param[in] _caller	New object caller of member function.
		*	\param[in] _func	New member function to bind.
		*	\param[in] _args	Args to pack.
		*/
		template <typename C>
		void Set(C* _caller, R(C::* _func)(Args...), Args... _args)
		{
			Function<R, Args...>::Set(_caller, _func);
			mArgs = std::tuple<Args...>{ std::forward<Args>(_args)... };
		}


		/**
		*	\brief Move operator
		*	Steal function handle (no additional memory allocation).
		*
		*	\param[in] _rhs		Function handle to move.
		*
		*	\return this.
		*/
		PackedFunction& operator=(PackedFunction&& _rhs) noexcept
		{
			Function<R, Args...>::operator=(std::move(_rhs));
			mArgs = std::move(_rhs.mArgs);

			return *this;
		}

		/**
		*	\brief Copy operator
		*	Additional memory allocation on member function copy.
		*
		*	\param[in] _rhs		Function handle to move.
		*
		*	\return this.
		*/
		PackedFunction& operator=(const PackedFunction& _rhs) noexcept
		{
			Function<R, Args...>::operator=(_rhs);
			mArgs = _rhs.mArgs;

			return *this;
		}

//}


//{ Execute

		/**
		*	\brief \b Execute bound function with packed args.
		*
		*	\return Bound function result value.
		*/
		R Execute() const
		{
			const Function<R, Args...>& fThis = *this;

			return std::apply(fThis, mArgs);
		}


		/**
		*	\brief \b Execute bound function with packed args operator.
		*
		*	\return Bound function result value.
		*/
		R operator()() const
		{
			return Execute();
		}

//}
	};


	/**
	*	\brief Template specialization for R(Args...) deduction.
	*
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class PackedFunction<R(Args...)> : public PackedFunction<R, Args...>
	{
	public:
		using PackedFunction<R, Args...>::PackedFunction;
		using PackedFunction<R, Args...>::operator=;
	};

// ##############################################################


// ##############################################################
// #					EVENT									#
// ##############################################################

	namespace intl
	{
		/**
		*	\brief Handle struct for an event-registered function.
		*
		*	\tparam R		Return type of function's declaration.
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename R, typename... Args>
		struct EventFuncHandle : public FuncHandle<R, Args...>
		{
			/// result ptr handle.
			R* result = nullptr;

			EventFuncHandle(R(*_func)(Args...), R* _result) noexcept :
				FuncHandle<R, Args...>(_func),
				result{ _result }
			{
			}

			bool Compare(const IFuncHandle<R, Args...>* _other) const override final
			{
				const EventFuncHandle* oFuncH = static_cast<const EventFuncHandle*>(_other);

				return FuncHandle<R, Args...>::Compare(_other) && result == oFuncH->result;
			}

			bool StoreResult(void* _inRes) override final
			{
				if (result)
				{
					*result = std::move(*static_cast<R*>(_inRes));

					return true;
				}

				return false;
			}
		};

		/**
		*	\brief Handle struct for an event-registered function with void return type.
		*
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename... Args>
		struct EventFuncHandle<void, Args...> : public FuncHandle<void, Args...>
		{
			EventFuncHandle(void(*_func)(Args...), void* _result) noexcept :
				FuncHandle<void, Args...>(_func)
			{
				(void)_result;
			}
		};


		/**
		*	\brief Handle struct for an event-registered member function.
		*
		*	\tparam R		Return type of function's declaration.
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename C, typename R, typename... Args>
		struct EventMemFuncHandle : public MemFuncHandle<C, R, Args...>
		{
			/// result ptr handle.
			R* result = nullptr;

			EventMemFuncHandle(C* _caller, R(C::* _func)(Args...), R* _result) noexcept :
				MemFuncHandle<C, R, Args...>(_caller, _func),
				result{ _result }
			{
			}

			bool Compare(const IFuncHandle<R, Args...>* _other) const override final
			{
				const EventMemFuncHandle* oFuncH = static_cast<const EventMemFuncHandle*>(_other);

				return MemFuncHandle<C, R, Args...>::Compare(_other) && result == oFuncH->result;
			}

			bool StoreResult(void* _inRes) override final
			{
				if (result)
				{
					*result = std::move(*static_cast<R*>(_inRes));

					return true;
				}

				return false;
			}
		};

		/**
		*	\brief Handle struct for an event-registered member function with void return type.
		*
		*	\tparam	Args	Argument types of function's declaration.
		*/
		template <typename C, typename... Args>
		struct EventMemFuncHandle<C, void, Args...> : public MemFuncHandle<C, void, Args...>
		{
			EventMemFuncHandle(C* _caller, void(C::* _func)(Args...), void* _result) noexcept :
				MemFuncHandle<C, void, Args...>(_caller, _func)
			{
				(void)_result;
			}
		};
	}


	/**
	*	\brief Event class.
	* 
	*	Template specialization for R(Args...) deduction.
	* 
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class Event
	{
		/// Registered functions.
		std::vector<intl::IFuncHandle<R, Args...>*> mFuncHandles;

	public:

//{ Constructors

		/// Default constructor.
		Event() = default;

		/// Default Move constructor.
		Event(Event&&) = default;

		/// Deleted Copy constructor.
		Event(const Event& _other) = delete;

		/// Destructor (auto clean).
		~Event()
		{
			Clear();
		}

//}


//{ Equals

		/**
		*	\brief Check whether this event is <b>empty</b> (no function registered).
		*
		*	\returns true if empty.
		*/
		bool IsEmpty() const noexcept
		{
			return mFuncHandles.empty();
		}

		/**
		*	\brief !IsEmpty bool operator.
		* 
		*	\return true if non empty.
		*/
		operator bool() const
		{
			return mFuncHandles.size();
		}

//}


//{ Clear

		/**
		*	\brief <b>Clear</b> all registered function.
		*	Free allocated memory.
		*/
		void Clear()
		{
			for (auto funcHandle : mFuncHandles)
			{
				delete funcHandle;
			}

			mFuncHandles.clear();
		}

		/**
		*	\brief <b>Clear</b> all registered function.
		*	Free allocated memory.
		*
		*	\return this
		*/
		Event& operator=(std::nullptr_t)
		{
			Clear();

			return *this;
		}

//}


//{ Add/Remove

		/**
		*	\brief <b>Add</b> a function to <b>register</b>.
		*
		*	Ensure <b>registered order</b> on execution.
		*
		*	\param[in] _func	Function to register.
		*	\param[in] _result	Optionnal result handle.
		*/
		void Add(R(*_func)(Args...), R* _result = nullptr)
		{
			//SA_ASSERT((Nullptr, _func), SA.Event.Event, L"Add nullptr function!");

			mFuncHandles.push_back(new intl::EventFuncHandle{ _func, _result });
		}

		/**
		*	\brief <b>Add</b> a member function to <b>register</b>.
		* 
		*	Ensure <b>registered order</b> on execution.
		* 
		*	\tparam C			Caller type.
		* 
		*	\param[in] _caller	Caller instance to call function from.
		*	\param[in] _func	Member function to register.
		*	\param[in] _result	Optionnal result handle.
		*/
		template <typename C>
		void Add(C* _caller, R(C::* _func)(Args...), R* _result = nullptr)
		{
			//SA_ASSERT((Nullptr, _caller), SA.Event.Event, L"Add nullptr caller!");
			//SA_ASSERT((Nullptr, _func), SA.Event.Event, L"Add nullptr function!");

			mFuncHandles.push_back(new intl::EventMemFuncHandle{ _caller, _func, _result });
		}

		/**
		*	\brief <b>Remove</b> a registered function.
		* 
		*	Start function iteration from <b>first</b> to <b>last</b> registered.
		* 
		*	\param[in] _func	Function to unregister.
		* 
		*	\returns true if successfully removed, otherwise false.
		*/
		bool Remove(R(*_func)(Args...), R* _result = nullptr)
		{
			//SA_ASSERT((Nullptr, _func), SA.Event.Event, L"Remove nullptr function!");

			intl::EventFuncHandle inHandle(_func, _result);

			for (auto it = mFuncHandles.begin(); it != mFuncHandles.end(); ++it)
			{
				if ((*it)->Compare(&inHandle))
				{
					mFuncHandles.erase(it);
					return true;
				}
			}

			return false;
		}

		/**
		*	\brief <b>Remove</b> a registered member function.
		*
		*	Start function iteration from <b>first</b> to <b>last</b> registered.
		*
		*	\param[in] _caller	Caller instance of registered function.
		*	\param[in] _func	Member function to unregister.
		*
		*	\returns true if successfully removed, otherwise false.
		*/
		template <typename C>
		bool Remove(C* _caller, R(C::* _func)(Args...), R* _result = nullptr)
		{
			//SA_ASSERT((Nullptr, _caller), SA.Event.Event, L"Add nullptr caller!");
			//SA_ASSERT((Nullptr, _func), SA.Event.Event, L"Add nullptr function!");

			intl::EventMemFuncHandle inHandle(_caller, _func, _result);

			for (auto it = mFuncHandles.begin(); it != mFuncHandles.end(); ++it)
			{
				if ((*it)->Compare(&inHandle))
				{
					mFuncHandles.erase(it);
					return true;
				}
			}

			return false;
		}

		/**
		*	\brief <b>Reverse Remove</b> a registered function.
		* 
		*	Start function iteration from <b>first</b> to <b>last</b> registered.
		* 
		*	\param[in] _func	Function to unregister.
		* 
		*	\returns true if successfully removed, otherwise false.
		*/
		bool RRemove(R(*_func)(Args...), R* _result = nullptr)
		{
			//SA_ASSERT((Nullptr, _func), SA.Event.Event, L"Remove nullptr function!");

			intl::EventFuncHandle inHandle(_func, _result);

			for (auto it = mFuncHandles.rbegin(); it != mFuncHandles.rend(); ++it)
			{
				if ((*it)->Compare(&inHandle))
				{
					// Convert rit to it.
					mFuncHandles.erase((it + 1).base());
					return true;
				}
			}

			return false;
		}

		/**
		*	\brief <b>Reverse Remove</b> a registered member function.
		*
		*	Start function iteration from <b>first</b> to <b>last</b> registered.
		*
		*	\param[in] _caller	Caller instance of registered function.
		*	\param[in] _func	Member function to unregister.
		*
		*	\returns true if successfully removed, otherwise false.
		*/
		template <typename C>
		bool RRemove(C* _caller, R(C::* _func)(Args...), R* _result = nullptr)
		{
			//SA_ASSERT((Nullptr, _caller), SA.Event.Event, L"Add nullptr caller!");
			//SA_ASSERT((Nullptr, _func), SA.Event.Event, L"Add nullptr function!");

			intl::EventMemFuncHandle inHandle(_caller, _func, _result);

			for (auto it = mFuncHandles.rbegin(); it != mFuncHandles.rend(); ++it)
			{
				if ((*it)->Compare(&inHandle))
				{
					// Convert rit to it.
					mFuncHandles.erase((it + 1).base());
					return true;
				}
			}

			return false;
		}


		/**
		*	\brief <b>Execute</b> all <b>registered</b> functions.
		* 
		*	Ensure <b>registered order</b> execution.
		* 
		*	\param[in] _args	Argument to forward to functions.
		*/
		void Execute(const Args&... _args)
		{
			for (auto func : mFuncHandles)
			{
				//SA_ASSERT(func)

				if constexpr (!std::is_void<R>::value)
				{
					R res = func->Execute(_args...);

					func->StoreResult(&res);
				}
				else
				{
					func->Execute(_args...);
				}
			}
		}

		/**
		*	\brief <b>Execute</b> all <b>registered</b> functions.
		*
		*	Ensure <b>registered order</b> execution.
		*
		*	\param[in] _results	Optionnal output results (append).
		*	\param[in] _args	Argument to forward to functions.
		*/
		void Execute(std::vector<R>& _results, const Args&... _args)
		{
			_results.reserve(mFuncHandles.size());

			for (size_t i = 0; i < mFuncHandles.size(); ++i)
			{
				R res = _results.emplace_back(mFuncHandles[i]->Execute(_args...));

				mFuncHandles[i]->StoreResult(&res);
			}
		}

//}


//{ Operators

		/**
		*	\brief Move operator.
		*
		*	\return this.
		*/
		Event& operator=(Event&& _other)
		{
			Clear();

			mFuncHandles = std::move(_other.mFuncHandles);

			return *this;
		}

		/**
		*	\brief Deleted copy operator.
		*
		*	\return this.
		*/
		Event& operator=(const Event&) = delete;


		/**
		*	\brief <b>Add</b> a function to <b>register</b>.
		* 
		*	Use Add() method.
		*
		*	\param[in] _func	Function to register.
		* 
		*	\returns This event.
		*/
		Event& operator+=(R(*_func)(Args...))
		{
			Add(_func);

			return *this;
		}

		/**
		*	\brief <b>Remove</b> a registered function.
		* 
		*	Use Remove() method.
		* 
		*	\param[in] _func	Function to unregister.
		* 
		*	\returns This event.
		*/
		Event& operator-=(R(*_func)(Args...))
		{
			Remove(_func);

			return *this;
		}


		/**
		*	\brief <b>Execute</b> all <b>registered</b> functions.
		* 
		*	Use Execute() method.
		*
		*	\param[in] _args	Argument to forward to functions.
		*/
		void operator()(const Args&... _args)
		{
			Execute(_args...);
		}

		/**
		*	\brief <b>Execute</b> all <b>registered</b> functions.
		* 
		*	Use Execute() method.
		*	Ensure <b>registered order</b> execution.
		* 
		*	\param[in] _results	Optionnal output results (append).
		*	\param[in] _args	Argument to forward to functions.
		*/
		void operator()(std::vector<R>& _results, const Args&... _args)
		{
			Execute(_results, _args...);
		}

//}
	};


	/**
	*	\brief Template specialization for R(Args...) deduction.
	*
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename R, typename... Args>
	class Event<R(Args...)> : public Event<R, Args...>
	{
	public:
		using Event<R, Args...>::Event;
		using Event<R, Args...>::operator=;
	};

// ##############################################################


// ##############################################################
// #					OWNED EVENT								#
// ##############################################################

	/**
	*	\brief Owned-Event class.
	*
	*	Event class with Execute-protected system.
	*	Only Owner class is allowed to call Execute().
	*
	*	\tparam OwnerT	Owner type.
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename OwnerT, typename R, typename... Args>
	class OwnedEvent : private Event<R(Args...)>
	{
		// Only OwnerT can call Execute.
		friend OwnerT;

		using Event<R(Args...)>::Execute;
		using Event<R(Args...)>::operator();

	public:
		using Event<R(Args...)>::Event;
		using Event<R(Args...)>::IsEmpty;
		using Event<R(Args...)>::operator bool;
		using Event<R(Args...)>::Clear;
		using Event<R(Args...)>::Add;
		using Event<R(Args...)>::Remove;
		using Event<R(Args...)>::RRemove;
		using Event<R(Args...)>::operator=;
		using Event<R(Args...)>::operator+=;
		using Event<R(Args...)>::operator-=;
	};


	/**
	*	\brief Template specialization for R(Args...) deduction.
	*
	*	\tparam R		Return type.
	*	\tparam Args	Argument types
	*/
	template <typename OwnerT, typename R, typename... Args>
	class OwnedEvent<OwnerT, R(Args...)> : public OwnedEvent<OwnerT, R, Args...>
	{
	public:
		using OwnedEvent<OwnerT, R, Args...>::OwnedEvent;
		using OwnedEvent<OwnerT, R, Args...>::operator=;
	};

// ##############################################################
}

#endif // EDO_SH_EVENT_GUARD
