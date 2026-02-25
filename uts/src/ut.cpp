#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../src/include/CChildren.hpp"
#include <memory>

struct CChild1Mock : CChild1
{
	public:
		MOCK_METHOD(void, destr, (), (override));
		virtual ~CChild1Mock() {destr(); }
};

TEST(MemoryManagement, Child1Destructor)
{
	using UPtrCChild1Mock = std::unique_ptr<CChild1Mock>;
	{
		std::unique_ptr<CChild1Mock> child1Mock(new CChild1Mock);
		EXPECT_CALL(*child1Mock, destr());
	}

}
