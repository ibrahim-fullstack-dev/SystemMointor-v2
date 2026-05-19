#pragma once

namespace System {

	namespace Interface {

		class ISchedulingProvider {
		public:
			// Virtual destructor for proper cleanup of derived classes.
			virtual ~ISchedulingProvider() = default;

			// Configures the current thread's priority with the OS kernel
			virtual bool SetBackgroundPriority() = 0;

			// Yields execution or forces the thread to sleep efficiently
			virtual void SleepFor(unsigned int milliseconds) = 0;
		};
	}
}
