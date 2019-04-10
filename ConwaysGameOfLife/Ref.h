#pragma once

template<typename T>
void _arrayDeleter(T* arr)
{
	delete[] arr;
}

class Object;

template<typename T>
class WeakRef;

/// <summary>
/// Represents the basic strong reference to any <see cref="Object"/>. This reference
/// will block the object from being destroyed.
/// </summary>
template<typename TType>
class Ref
{
	// This condition is making a fix for reference types. All classes derrived from Object are considered a reference type.
	// Condition checks if TType is an array and a class derrived from Object, i.e. TType = MyClass[]. If the condition is true
	// then the T argument is boxed inside another Ref<...>. This allows for writing Ref<MyClass[]> myVar; which underhood creates
	// a Ref<Ref<MyClass>[]> variable. Because of this all Ref's to arrays with an reference type as an element will be
	// treated as arrays to Ref's to that element.
	using T = std::conditional_t<
			std::conjunction_v<std::is_array<TType>, std::is_assignable<Object&, std::remove_all_extents_t<TType>&>>, 
			Ref<std::remove_all_extents_t<TType>>,
			std::remove_all_extents_t<TType>
		>;

	// When we are currently in Ref<const T> we must add Ref<T> as a friend.
	friend class Ref<std::remove_const_t<T>>;
	// Similalry when we are in Ref<T> we must add Ref<const T> as a friend.
	friend class Ref<std::add_const_t<T>>;
private:
	// The pointer holding the actual object.
	std::shared_ptr<T> ptr;

public:
	/// <summary>
	/// Checks if two references of the same types are equal.
	/// </summary>
	static bool referenceEquals(const Ref<const T>& first, const Ref<const T>& second)
	{
		return first.ptr == second.ptr;
	}

	/// <summary>
	/// Creates an empty reference.
	/// </summary>
	Ref()
	{

	}

	/// <summary>
	/// Destroys the reference.
	/// </summary>
	~Ref() 
	{

	}

	/// <summary>
	/// Creates an reference to the object pointer. Takes the authority of the specified
	/// pointer which means after creation the pointer must no longer be used for 
	/// other operations. Used to easly create references to object from new keyword.
	/// </summary>
	Ref(T* ptr)
	{
		if(std::is_array_v<TType>)
			this->ptr = std::shared_ptr<T>(ptr, _arrayDeleter<T>);
		else
			this->ptr = std::shared_ptr<T>(ptr);
	}

	/// <summary>
	/// Creates a reference from the shared_ptr. Allows to convert shared_ptr to 
	/// references. Used mainly in convienient conversions from shared_ptr.
	/// </summary>
	Ref(const std::shared_ptr<T>& ptr)
	{
		this->ptr = ptr;
	}

	/// <summary>
	/// Creates a reference by copying the value from the other reference.
	/// </summary>
	Ref(const Ref<T>& other)
	{
		ptr = other.ptr;
	}

	/// <summary>
	/// Allows for converting Ref&lt;T&gt; to Ref&lt;const T&gt; implicitly. Only
	/// enabled if current class contains const T type parameter.
	/// </summary>
	template<typename = std::enable_if<std::is_const<T>::value>>
	Ref(const Ref<std::remove_const_t<T>>& other)
	{
		ptr = other.ptr;
	}

	/// <summary>
	/// Allows for moving the reference. Makes returning refernces creating
	/// less copies of the shared pointers.
	/// </summary>
	Ref(const Ref<T>&& other)
	{
		ptr = std::move(other.ptr);
	}

	/// <summary>
	/// Allows for copying the reference using the assign operator.
	/// </summary>
	const Ref<T>& operator=(const Ref<T>& other)
	{
		ptr = other.ptr;
		return *this;
	}

	/// <summary>
	/// Allows for fast access to the T object members.
	/// </summary>
	T* operator->() const
	{
		return ptr.operator->();
	}

	/// <summary>
	/// Compares current reference to other const one. Enabled only if compared reference is
	/// not reference to object.
	/// </summary>
	template<typename = std::enable_if_t<std::negation<std::is_same<T, Object>>::value>>
	bool operator==(const Ref<const T>& right) const
	{
		// If both references are null the they are equal.
		if (operator!() && !right)
			return true;

		// At this point when current reference or other reference is null 
		// then references are not equal.
		if (operator!() || !right)
			return false;

		// Delegates the check to Object equals operator so it can use it's 
		// overridable equals method.
		return *ptr == *right.ptr;
	}

	/// <summary>
	/// Compares current reference to other non const reference. Enabled only if compared 
	/// reference is not const reference.
	/// </summary>
	template<typename = std::enable_if_t<std::negation<std::is_const<T>>::value>>
	bool operator==(const Ref<std::remove_const_t<T>>& right) const
	{
		// If both references are null the they are equal.
		if (operator!() && !right)
			return true;

		// At this point when current reference or other reference is null 
		// then references are not equal.
		if (operator!() || !right)
			return false;

		// Get both objects and delegate the compare to the Object equals operator.
		const Object& first = *ptr;
		const Object& second = *right.ptr;
		
		return first == second;
	}

	/// <summary>
	/// Cehcks if the current reference is referencing the same object as the 
	/// specified pointer.
	/// </summary>
	bool operator==(const T* right) const
	{
		return ptr.get() == right;
	}

	/// <summary>
	/// Cehcks if the current reference is not referencing the same object as the 
	/// specified pointer.
	/// </summary>
	bool operator!=(const T* right) const
	{
		return ptr.get() != right;
	}

	/// <summary>
	/// Checks if current reference is an empty one.
	/// </summary>
	bool operator!() const
	{
		return !ptr;
	}

	/// <summary>
	/// Allows for explicit casting from the one reference to another. Enabled only
	/// if the type to which the reference is casted is assignable from current type 
	/// and vice versa.
	/// </summary>
	template<typename T2, typename = std::enable_if_t<(std::is_assignable<T2&, T&>::value || std::is_assignable<T&, T2&>::value)>>
	inline explicit operator Ref<T2>() const
	{
		return cast<T2>();
	}

	/// <summary>
	/// Allows for implicit casting from the one reference to another. Enabled only
	/// if the type to which the reference is casted is assignable from current type.
	/// </summary>
	template<typename T2, typename = std::enable_if_t<std::is_assignable<T2&, T&>::value>>
	inline operator Ref<T2>()
	{
		return cast<T2>();
	}

	/// <summary>
	/// Checks if current reference is not an empty one.
	/// </summary>
	inline operator bool() const
	{
		return !!ptr;
	}

	/// <summary>
	/// Performs dynamic cast to the specified type. If current refernce is not
	/// assignable to the specified type then empty reference is returned.
	/// </summary>
	template<typename T2>
	inline Ref<T2> as() const
	{
		return std::dynamic_pointer_cast<T2>(ptr);
	}

	/// <summary>
	/// Performs static cast to the specified type. Enabled only if the type to 
	/// which the reference is casted is assignable from current type 
	/// and vice versa. 
	/// </summary>
	template<typename T2, typename = std::enable_if_t<(std::is_assignable<T2&, T&>::value || std::is_assignable<T&, T2&>::value)>>
	inline Ref<T2> cast() const
	{
		return std::static_pointer_cast<T2>(ptr);
	}

	/// <summary>
	/// Performs dynamic type check. If current refernce is not
	/// assignable to the specified type then false is returned.
	/// </summary>
	template<typename T2>
	inline bool is() const
	{
		// When ptr is null then the check fails because we cannot cast 
		// an empty ptr to T2.
		if (!ptr)
			return false;

		return !!std::dynamic_pointer_cast<T2>(ptr);
	}

	/// <summary>
	/// Allows for easy access to the array elements when TType is an array.
	/// </summary>
	template<typename = std::enable_if_t<std::is_array_v<TType>>>
	T& operator[](size_t index) const
	{
		return this->operator->()[index];
	}

	// We need to add WeakRef<T> as a friend so it can use internal
	// shared pointer.
	friend class WeakRef<T>;
};

/// <summary>
/// Represents a weak reference to the <see cref="Object"/>. This reference will
/// not block the object from being destroyed.
/// </summary>
template<typename T>
class WeakRef
{
private:
	// The weak pointer that actually stores the object.
	std::weak_ptr<T> ptr;

public:
	/// <summary>
	/// Creates an empty weak reference.
	/// </summary>
	WeakRef()
	{

	}

	/// <summary>
	/// Creates a weak reference referencing specified object pointed by shared pointer.
	/// </summary>
	WeakRef(const std::shared_ptr<T>& ptr)
	{
		this.ptr = std::weak_ptr<T>(ptr);
	}

	/// <summary>
	/// Creates a weak reference from strong reference.
	/// </summary>
	WeakRef(const Ref<T>& ref)
	{
		ptr = std::weak_ptr<T>(ref.ptr);
	}

	/// <summary>
	/// Creates a weak reference from another weak reference.
	/// </summary>
	WeakRef(const WeakRef<T>& other)
	{
		ptr = std::weak_ptr<T>(other.ptr);
	}

	/// <summary>
	/// Allows for assigning a reference to the weak reference.
	/// </summary>
	const WeakRef<T>& operator=(const Ref<T>& other)
	{
		ptr = std::weak_ptr<T>(other.ptr);
		return *this;
	}

	/// <summary>
	/// Allows for assigning another weak reference to the current weak reference.
	/// </summary>
	const WeakRef<T>& operator=(const WeakRef<T>& other)
	{
		ptr = std::weak_ptr<T>(other.ptr);
		return *this;
	}

	/// <summary>
	/// Checks if current reference is an empty one.
	/// </summary>
	inline bool operator!() const
	{
		return !ptr;
	}

	/// <summary>
	/// Gets the target of the weak reference. If the target no longer exists
	/// returning reference will be empty.
	/// </summary>
	inline Ref<T> target() const
	{
		return ptr.lock();
	}
};