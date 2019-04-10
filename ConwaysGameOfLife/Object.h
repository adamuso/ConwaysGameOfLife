#pragma once

#include <memory>
#include <cassert>
#include "Ref.h"

/// <summary>
/// Represents the basic object class that allows for creating managed 
/// objects in the program.
/// </summary>
class Object : public std::enable_shared_from_this<Object>
{
protected:
	/// <summary> 
	/// Conversion to reference of any type. This allows fast assigning from 
	/// dereferenced this variable to the reference.
	/// </summary>
	template<typename T>
	operator Ref<T>()
	{
		return std::static_pointer_cast<T>(this->shared_from_this());
	}

	/// <summary> 
	/// Conversion to cosnt reference of any type. This allows fast assigning from 
	/// dereferenced this variable inside const method to the reference.
	/// </summary>
	template<typename T>
	operator const Ref<const T>() const
	{
		return std::static_pointer_cast<const T>(this->shared_from_this());
	}

public:
	/// <summary>
	/// Destroys the object.
	/// </summary>
	virtual ~Object() { }

	/// <summary>
	/// Checks if two different references reference to the same object in the memory.
	/// </summary>
	static bool referenceEquals(const Ref<const Object> first, const Ref<const Object> second)
	{
		return Ref<Object>::referenceEquals(first, second);
	}

	/// <summary>
	/// Checks if two different object are equal to each other.
	/// </summary>
	static bool equals(const Ref<const Object> first, const Ref<const Object> second)
	{
		// Checks if boths references are null
		if (!first && !second)
			return true;

		// At this point one of the references is null obejcts are not equal
		if (!first || !second)
			return false;

		return first->equals(second);
	}

	/// <summary>
	/// Checks if current object is equal to other referenced object.
	/// </summary>
	virtual bool equals(const Ref<const Object> other) const 
	{ 
		// By default objects are compared by their references.
		return referenceEquals(*this, other);
	}	

	/// <summary>
	/// Checks if the current object is equal to the another object.
	/// </summary>
	virtual bool operator==(const Object& other) const
	{
		return equals(other);
	}

	/// <summary>
	/// Checks if the current object is not equal to the another object.
	/// </summary>
	virtual bool operator!=(const Object& other) const
	{
		return !equals(other);
	}
};