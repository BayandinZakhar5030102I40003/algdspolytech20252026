#include <gtest/gtest.h>
// #include "labA.h"

extern "C" {
// #include "C:\Users\....\labA.h"
#include "labA.h"
}

class ListTest : public ::testing::Test {
 protected:
  void SetUp() override { list = createL(); }

  void TearDown() override {}

  listS* list = nullptr;
};

TEST_F(ListTest, CreateElValidElem_n1) {
  elementS* elem = createE();

  ASSERT_NE(elem, nullptr);
  EXPECT_EQ(elem->siz, 0);
  EXPECT_EQ(elem->next, nullptr);

  free(elem);
}

TEST_F(ListTest, CreateLsEmptyList_n2) {
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(list->siz, 0);
  EXPECT_EQ(list->start, nullptr);
  EXPECT_EQ(list->end, nullptr);
}

TEST_F(ListTest, CreateItEmptyList_3n) {
  IteratorS iter = createI(list);

  EXPECT_EQ(iter.list, list);
  EXPECT_EQ(iter.elem, nullptr);
  EXPECT_EQ(iter.i, 0);
}

TEST_F(ListTest, CreateItNonEmptyList_n4) {
  add(list, 10);
  add(list, 20);

  IteratorS iter = createI(list);

  EXPECT_EQ(iter.list, list);
  EXPECT_NE(iter.elem, nullptr);
  EXPECT_EQ(iter.elem, list->start);
  EXPECT_EQ(iter.i, 0);
}

TEST_F(ListTest, AddToEmptyList_n5) {
  int result = add(list, 1);

  EXPECT_EQ(result, 1);
  EXPECT_EQ(list->siz, 1);
  EXPECT_NE(list->start, nullptr);
  EXPECT_NE(list->end, nullptr);
  EXPECT_EQ(list->start->siz, 1);
  EXPECT_EQ(list->start->bigdata[0], 1);
}

TEST_F(ListTest, AddElemBlockSize_n6) {
  const int count = 15;

  for (int i = 0; i < count; i++) {
    int result = add(list, i * 10);
    EXPECT_EQ(result, 1);
  }

  EXPECT_EQ(list->siz, count + 1);
  EXPECT_NE(list->start->next, nullptr);
}

TEST_F(ListTest, AddNullList_n7) {
  int result = add(nullptr, 1);
  EXPECT_EQ(result, 0);
}

TEST_F(ListTest, AddFilloneBlock_n8) {
  for (int i = 0; i < szE; i++) {
    add(list, i + 1);
  }

  EXPECT_EQ(list->siz, szE);
  EXPECT_EQ(list->start->siz, szE);
  EXPECT_EQ(list->end->siz, szE);
  EXPECT_EQ(list->start, list->end);
}

TEST_F(ListTest, FindLsExistElem_n9) {
  add(list, 10);
  add(list, 20);

  int index = findL(list, 20);
  EXPECT_EQ(index, 1);
}

TEST_F(ListTest, FindLsNonExistElem_n10) {
  add(list, 10);
  add(list, 20);

  int index = findL(list, 999);
  EXPECT_EQ(index, 0);
}

TEST_F(ListTest, FindElValidInd_n11) {
  add(list, 100);
  add(list, 200);
  add(list, 300);

  int element = 0;
  int result = findE(list, 1, &element);

  EXPECT_EQ(result, 1);
  EXPECT_EQ(element, 200);
}

TEST_F(ListTest, FindElInvalidInd_n12) {
  add(list, 100);
  add(list, 200);

  int element = 0;
  int result = findE(list, 5, &element);

  EXPECT_EQ(result, 0);
}

TEST_F(ListTest, FindElEmptyList_13) {
  int element = 0;
  int result = findE(list, 0, &element);
  EXPECT_EQ(result, 0);
}

TEST_F(ListTest, DeleteElInvalidInd_n14) {
  add(list, 10);
  add(list, 20);

  int result = deleteE(list, 5);

  EXPECT_EQ(result, 0);
  EXPECT_EQ(countE(list), 2);
}

TEST_F(ListTest, DeleteElEmptyList_n15) {
  int result = deleteE(list, 0);
  EXPECT_EQ(result, 0);
}

TEST_F(ListTest, DeleteElFirstElem_n16) {
  add(list, 100);
  add(list, 200);
  add(list, 300);

  int result = deleteE(list, 0);

  EXPECT_EQ(result, 1);
  EXPECT_EQ(list->siz, 2);

  int first_element = 0;
  findE(list, 0, &first_element);
  EXPECT_EQ(first_element, 200);
}

TEST_F(ListTest, DeleteElMiddLE_n17) {
  for (int i = 0; i < 5; i++) {
    add(list, i * 10);
  }
  int count1 = countE(list);
  int result = deleteE(list, 2);

  EXPECT_EQ(result, 1);
  EXPECT_EQ(countE(list), count1 - 1);
}

TEST_F(ListTest, DeleteElLastElem_n18) {
  add(list, 100);
  add(list, 200);
  add(list, 300);

  int result = deleteE(list, 2);

  EXPECT_EQ(result, 1);
  EXPECT_EQ(list->siz, 2);

  int last_element = 0;
  findE(list, 1, &last_element);
  EXPECT_EQ(last_element, 200);
}

TEST_F(ListTest, CountElEmptyList_n19) {
  int count = countE(list);
  EXPECT_EQ(count, 0);
}

TEST_F(ListTest, CountElAfterAdd_n20) {
  add(list, 1);
  add(list, 2);
  add(list, 3);

  int count = countE(list);
  EXPECT_EQ(count, 3);
}

TEST_F(ListTest, IteratedAllElems_n21) {
  add(list, 1);
  add(list, 2);
  add(list, 3);

  IteratorS iter = createI(list);
  int value;
  int count = 0;
  int sum = 0;

  while (iterated(&iter, &value)) {
    count++;
    sum += value;
  }

  EXPECT_EQ(count, 3);
  EXPECT_EQ(sum, 6);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
