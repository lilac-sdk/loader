#pragma once
#include <vector>

namespace geode::core::hook {
	template <typename T>
	class Platform {
	public:
		static constexpr const std::vector<std::byte> getTrap() {
			static_assert(&T::trap, "implement trap");
            return T::trap;
        }

        static constexpr const size_t getTrapSize() {
        	static_assert(&T::trap, "implement trap");
            return sizeof(T::trap);
        }

        static constexpr const std::vector<std::byte> getJump(const void* from, const void* to) {
			static_assert(&T::jump, "implement jump");
            return T::jump(from, to).data();
        }

        static constexpr const size_t getJumpSize(const void* from, const void* to) {
        	static_assert(&T::trap, "implement trap");
            return T::jump(from, to).size();
        }

	    static bool writeMemory(const void* to, const void* from, const size_t size) {
	    	static_assert(&Platform<T>::write_memory != &T::write_memory, "implement writeMemory");
	        return T::writeMemory(to, from, size);
	    }

	    // static bool readMemory(const void* addr, const void* to, const size_t size) {
	    // 	static_assert(&Platform<T>::read_memory != &T::read_memory, "implement readMemory");
	    //     return T::readMemory(addr, to, size);
	    // }

	    static bool initialize() {
	    	static_assert(&Platform<T>::initialize != &T::initialize, "implement initialize");
	        return T::initialize();
	    }

	    static bool enableSingleStep(void* context) {
	    	static_assert(&Platform<T>::enableSingleStep != &T::enableSingleStep, "implement enableSingleStep");
	        return T::enableSingleStep(context);
	    }

	    static bool disableSingleStep(void* context) {
	    	static_assert(&Platform<T>::disableSingleStep != &T::disableSingleStep, "implement disableSingleStep");
	        return T::disableSingleStep(context);
	    }
	};
}
