#pragma once

#include <assert.h>
#include <stdint.h>
#include <cstdio>

namespace Engine {

	typedef uint64_t	ref_counter_t;

	struct ReferenceCounters
	{
		ref_counter_t		OwnerReferences;
		ref_counter_t		ObserverReferences;

		ReferenceCounters(ref_counter_t i_InitialOwners, ref_counter_t i_InitialObservers) :
			OwnerReferences(i_InitialOwners),
			ObserverReferences(i_InitialObservers)
		{ }

		bool isEmpty() {
			return (ObserverReferences == 0) && (OwnerReferences == 0);
		}

		bool HasOwner() {
			return (OwnerReferences != 0);
		}
	};

	// forward declare Observing pointer as we'll refer to it in OwningPointer definition
	template<class T>
	class ObservingPointer;

	template<class T>
	class OwningPointer

	{
		template<class U>
		friend class ObservingPointer;

		template<class U>
		friend class OwningPointer;
	private:
		// underlying object
		T* OwningObject;

		// ref count
		ReferenceCounters* CountRef;
	public:
		// Default Constructor
		OwningPointer() {
			OwningObject = nullptr; 
			CountRef = nullptr;
		}

		// Standard Constructor
		explicit OwningPointer(T * i_ptr) : OwningObject(i_ptr) {
			CountRef = new ReferenceCounters(1, 0);
		}

		explicit OwningPointer(const T &i) {
			OwningObject = new T(i);
			//OwningObject = &i;
			CountRef = new ReferenceCounters(1, 0);
		}

		OwningPointer(std::nullptr_t i_null) {
			OwningObject = nullptr;
			CountRef = nullptr;
		}
		// Copy Constructor
		OwningPointer(const OwningPointer & i_other) {
			/*ReleaseCurrentOwningPointer();*/
			OwningObject = i_other.OwningObject;
			CountRef = i_other.CountRef;
			if (CountRef)
				CountRef->OwnerReferences++;
		}

		void ReleaseOwningObject() {
			delete OwningObject;
		}

		void ReleaseCurrentOwningPointer() {
			if (CountRef) {
				CountRef->OwnerReferences--;
				if (!CountRef->HasOwner()) {
					ReleaseOwningObject();
					if (CountRef->isEmpty()) {
						delete CountRef;
					}
				}
			}
			OwningObject = nullptr;
			CountRef = nullptr;
		}
		ReferenceCounters& GetReferenceCounters() {
			return *CountRef;
		}

		// Copy Constructor between polymorphic types
		// OwningPointer<Base> BasePtr( new Base() );
		// OwningPointer<Default> DefaultPtr = BasePtr; <-- Used here
		template<class U>
		OwningPointer(const OwningPointer<U> & i_other) {
			//ReleaseCurrentOwningPointer();
			OwningObject = reinterpret_cast<T*>(i_other.OwningObject);
			CountRef = i_other.CountRef;
			if (CountRef)
				CountRef->OwnerReferences++;
		}

		// Copy Constructor - For creating an Owning Pointer from an Observing Pointer
		// Will create a OwningPointer that points to nullptr if the referenced object has been destroyet (no more Owners left, just Observers)
		OwningPointer(const ObservingPointer<T> & i_other) {
			//ReleaseCurrentOwningPointer();
			OwningObject = i_other.AcquireOwnership().OwningObject;
			CountRef = i_other.AcquireOwnership().CountRef;
			if (CountRef)
				CountRef->OwnerReferences++;
		}

		// Copy Constructor - For creating an Owning Pointer of a polymorphic type from an Observing Pointer
		template<class U>
		OwningPointer(const ObservingPointer<U> & i_other) {
			//ReleaseCurrentOwningPointer();
			OwningObject = (T)i_other.AcquireOwnership().OwningObject;
			CountRef = i_other.AcquireOwnership().CountRef;
			if (CountRef)
				CountRef->OwnerReferences++;
		}

		/*void operator=(OwningPointer & i_other) {
			if (*this != i_other) {
				ReleaseCurrentOwningPointer();
				OwningObject = i_other.OwningObject;
				CountRef = i_other.CountRef;
			}
		}*/

		// Assignment Operator
		void operator=(const OwningPointer & i_other) {
			if (*this != i_other) {
				ReleaseCurrentOwningPointer();
				OwningObject = i_other.OwningObject;
				CountRef = i_other.CountRef;
				if (CountRef)
					CountRef->OwnerReferences++;
			}
		}

		// Assignment Operator between polymorphic types
		template<class U>
		void operator=(const OwningPointer<U> & i_other) {
			if (*this != i_other) {
				ReleaseCurrentOwningPointer();
				OwningObject = reinterpret_cast<T*>(i_other.OwningObject);
				CountRef = i_other.CountRef;
				if (CountRef)
					CountRef->OwnerReferences++;
			}
		}

		// Assignment Operator - Reassigns an existing Owning Pointer from an existing Observing Pointer
		void operator=(const ObservingPointer<T> & i_other) {
			if (*this != i_other) {
				ReleaseCurrentOwningPointer();
				OwningObject = i_other.AcquireOwnership().OwningObject;
				CountRef = i_other.AcquireOwnership().CountRef;
				if (CountRef)
					CountRef->OwnerReferences++;
			}
		}

		// Assignment Operator - Reassigns an existing Owning Pointer from an existing Observing Pointer of a polymorphic type
		template<class U>
		void operator=(const ObservingPointer<U> & i_other) {
			if (*this != i_other) {
				ReleaseCurrentOwningPointer();
				OwningObject = (T)i_other.AcquireOwnership().OwningObject;
				CountRef = i_other.AcquireOwnership().CountRef;
				if (CountRef)
					CountRef->OwnerReferences++;
			}
		}

		// Assignment Operator - null specific
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = nullptr;
		// Don't really need to implement this. If it's not here it'll go through OwningPointer & operator=( OwningPointer & i_other);
		void operator=(std::nullptr_t i_null) {
			if (*this != nullptr) {
				ReleaseCurrentOwningPointer();
			}
			OwningObject = nullptr;
			CountRef = nullptr;
		}

		// Assignment Operator - Assigning directly from an existing pointer
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = new Base();
		void operator=(T * i_ptr) {
			if (*this != i_ptr) {
				ReleaseCurrentOwningPointer();
				OwningObject = i_ptr;
				CountRef = new ReferenceCounters(1, 0);
			}
		}

		//OwningPointer & operator=(T i) {
		//	ReleaseCurrentOwningPointer();
		//	OwningObject = new T(i);
		//	CountRef = new ReferenceCounters(1, 0);
		//}

		// Destructor
		~OwningPointer() {
			ReleaseCurrentOwningPointer();
		}

		// Equality comparison operator
		inline bool operator==(const OwningPointer<T> & i_other) const {
			return (OwningObject == i_other.OwningObject);
		}

		// Equality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator==(const OwningPointer<U> & i_other) const {
			return (OwningObject == i_other.OwningObject);
		}

		// Equality comparison operator for comparing to an Observing Pointer
		inline bool operator==(const ObservingPointer<T> & i_other) const {
			return (OwningObject == i_other.OwningObject);
		}

		// Equality comparison operator for comparing to an Observing Pointer of a polymorphic type
		template<class U>
		inline bool operator==(const ObservingPointer<U> & i_other) const {
			return (OwningObject == reinterpret_cast<T*>(i_other.OwningObject));
		}

		// Inequality comparison operator
		inline bool operator!=(const OwningPointer<T> & i_other) const {
			return (OwningObject != i_other.OwningObject);
		}

		// Inequality comparison operator between pointers to polymorphic types
		template<class U>
		inline bool operator!=(const OwningPointer<U> & i_other) const {
			return (OwningObject != i_other.OwningObject);
		}

		// Inequality comparison operator for comparing to an Observing Pointer
		inline bool operator!=(const ObservingPointer<T> & i_other) const {
			return (*this != i_other.AcquireOwnership());
		}

		// Inequality comparison operator for comparing to an Observing Pointer of a polymorphic type
		template<class U>
		inline bool operator!=(const ObservingPointer<U> & i_other) const {
			return (*this != i_other.AcquireOwnership());
		}

		// Equality comparison operator directly to pointer 
		inline bool operator==(T * i_ptr) const {
			return (OwningObject == i_ptr);
		}

		// Equality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator==(U * i_ptr) const {
			return (OwningObject == i_ptr);
		}

		// Equality comparison operator for nullptr
		inline bool operator==(std::nullptr_t nullp) const {
			return (OwningObject == nullptr);
		}

		// Inequality comparison operator directly to pointer 
		inline bool operator!=(T * i_ptr) const {
			return (OwningObject != i_ptr);
		}

		// Inequality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator!=(U * i_ptr) const {
			return (OwningObject != i_ptr);
		}

		// Inequality comparison operator for nullptr
		inline bool operator!=(std::nullptr_t nullp) const {
			return (OwningObject != nullptr);
		}

		// bool operator - shorthand for != nullptr;
		inline operator bool() const {
			return (OwningObject != nullptr);
		}

		// member access operator
		T * operator->() {
			return OwningObject;
		}

		// indirection operator
		T & operator*() const {
			if (OwningObject == nullptr) {
				printf("!!!");
			}
			assert(OwningObject != nullptr);
			return *OwningObject;
		}
		T* OriginalPointer() {
			return OwningObject;
		}
	};

	template<class T>
	class ObservingPointer
	{
		template<class U>
		friend class OwningPointer;
		template<class U>
		friend class ObservingPointer;
	private:
		T* OwningObject;
		ReferenceCounters* CountRef;
	public:
		// Default Constructor
		ObservingPointer() {
			OwningObject = nullptr;
			CountRef = nullptr;
		}

		ObservingPointer(std::nullptr_t inull) {
			OwningObject = nullptr;
			CountRef = nullptr;
		}

		// Copy Constructors
		ObservingPointer(const ObservingPointer & i_other) {
			OwningObject = i_other.OwningObject;
			CountRef = i_other.CountRef;
			if (CountRef)
				CountRef->ObserverReferences++;
		}

		template<class U>
		ObservingPointer(const OwningPointer<U> & i_owner) {
			OwningObject = reinterpret_cast<T*>(i_owner.OwningObject);
			CountRef = i_owner.CountRef;
			if (CountRef)
				CountRef->ObserverReferences++;
		}

		template<class U>
		ObservingPointer(const ObservingPointer<U> & i_other) {
			OwningObject = reinterpret_cast<T*>(i_other.OwningObject);
			CountRef = i_other.CountRef;
			if (CountRef)
				CountRef->ObserverReferences++;
		}

		// Destructor
		~ObservingPointer() {
			ReleaseCurrentCurrentObservingPointer();
		}

		void ReleaseCurrentCurrentObservingPointer() {
			if (CountRef) {
				CountRef->ObserverReferences--;
				if (CountRef->isEmpty()) {
					delete CountRef;
				}
			}
			OwningObject = nullptr;
			CountRef = nullptr;
		}

		// Assignment operators
		void operator=(const ObservingPointer & i_other) {
			if (*this != i_other) {
				ReleaseCurrentCurrentObservingPointer();
				OwningObject = i_other.OwningObject;
				CountRef = i_other.CountRef;
				if (CountRef)
					CountRef->ObserverReferences++;
			}
		}

		template<class U>
		void operator=(const ObservingPointer<U> & i_other) {
			if (*this != i_other) {
				ReleaseCurrentCurrentObservingPointer();
				OwningObject = i_other.OwningObject;
				CountRef = i_other.CountRef;
				if (CountRef)
					CountRef->ObserverReferences++;
			}
		}

		template<class U>
		inline void operator=(const OwningPointer<U> & i_other) {
			if (*this != i_other) {
				ReleaseCurrentCurrentObservingPointer();
				OwningObject = i_other.OwningObject;
				CountRef = i_other.CountRef;
				if (CountRef)
					CountRef->ObserverReferences++;
			}
		}

		void operator=(std::nullptr_t i_null) {
			ReleaseCurrentCurrentObservingPointer();
			OwningObject = nullptr;
			CountRef = nullptr;
		}

		// Create an Owning Pointer from this Observering Pointer
		inline OwningPointer<T> AcquireOwnership() {
			return OwningPointer<T>(OwningObject);
		}

		// Equality comparison operators
		inline bool operator==(const OwningPointer<T> & i_other) const {
			return (OwningObject == i_other.OwningObject);
		}

		template<class U>
		inline bool operator==(const OwningPointer<U> & i_other) const {
			return (OwningObject == i_other.OwningObject);
		}

		inline bool operator==(const ObservingPointer<T> & i_other) const {
			return (OwningObject == i_other.OwningObject);
		}

		template<class U>
		inline bool operator==(const ObservingPointer<U> & i_other) const {
			return (OwningObject == i_other.OwningObject);
		}

		inline bool operator==(T * i_ptr) const {
			return (OwningObject == i_ptr);
		}

		template<class U>
		inline bool operator==(U * i_ptr) const {
			return(OwningObject == i_ptr);
		}

		// Inequality comparison operators
		inline bool operator!=(const OwningPointer<T> & i_other) const {
			return (OwningObject != i_other.OwningObject);
		}

		template<class U>
		inline bool operator!=(const OwningPointer<U> & i_other) const {
			return (OwningObject != i_other.OwningObject);
		}

		inline bool operator!=(const ObservingPointer<T> & i_other) const {
			return (OwningObject != i_other.OwningObject);
		}

		template<class U>
		inline bool operator!=(const ObservingPointer<U> & i_other) const {
			return (OwningObject != i_other.OwningObject);
		}

		inline bool operator!=(T * i_ptr) const {
			return (OwningObject != i_ptr);
		}

		template<class U>
		inline bool operator!=(U * i_ptr) const {
			return (OwningObject != i_ptr);
		}

		T * operator->() {
			return OwningObject;
		}

		// indirection operator
		T & operator*() const {
			assert(OwningObject != nullptr);
			return *OwningObject;
		}

		T* OriginalPointer() {
			return OwningObject;
		}


		// bool operator
		inline operator bool() const {
			return (OwningObject != nullptr);
		}
	};

} // namespace Engine