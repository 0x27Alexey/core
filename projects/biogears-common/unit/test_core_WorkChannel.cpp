//! Copyright/' (C) Applied Research Associates - All Rights Reserved
//! Unauthorized copying of this file, via any medium is strictly prohibited
//! Proprietary and confidential
//!
//! This file is subject to the terms and conditions defined in file
//! 'LICENSE.txt', which is part of this source code package

//!
//! @author David Lee
//! @date   2017 Aug 3rd
//!
//! Unit Test for NGSS Config
//!
#include <thread>

#include <gtest/gtest.h>

#include <ara/threading/thread_work_channel.tci.h>
#include <ara/container/concurrent_queue.tci.h>

#ifdef DISABLE_KALE_WorkChannel_TEST
  #define TEST_FIXTURE_NAME DISABLED_WorkChannel_Fixture
#else
  #define TEST_FIXTURE_NAME WorkChannel_Fixture
#endif


// The fixture for testing class Foo.
class TEST_FIXTURE_NAME : public ::testing::Test {
protected:
  // You can do set-up work for each test here.
  TEST_FIXTURE_NAME() = default;

  // You can do clean-up work that doesn't throw exceptions here.
  virtual ~TEST_FIXTURE_NAME() = default;

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  // Code here will be called immediately after the constructor (right
  // before each test).
  virtual void SetUp();

  // Code here will be called immediately after each test (right
  // before the destructor).
  virtual void TearDown();
};

void TEST_FIXTURE_NAME::SetUp()
{
}

void TEST_FIXTURE_NAME::TearDown()
{

}

TEST_F(TEST_FIXTURE_NAME, WorkChannel_Construction)
{
  auto channel = ara::ThreadWorkChannel<void(void)>::make_shared();
  
  auto source = channel->as_source();
  auto sink   = channel->as_sink();
}

TEST_F(TEST_FIXTURE_NAME, WorkChannel_push_pop)
{
  auto channel = ara::ThreadWorkChannel<int(void)>::make_shared();

  int value = 5;
  auto source = channel->as_source();
  auto sink = channel->as_sink();

	source->insert([](){return 1;});
	source->insert([](){return 2;});
	source->insert([](){return 3;});

	EXPECT_EQ(sink->consume()(), 1);
	EXPECT_EQ(sink->consume()(), 2);
	EXPECT_EQ(sink->consume()(), 3);
}
