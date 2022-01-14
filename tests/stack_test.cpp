#include "datastructures/stack.hpp"

#include <stack>

#include "datastructures/linkedlist.hpp"
#include "testing.hpp"

void StackTest() {
    Assert it("Stack tests");
    Stack<int> stack;

    it.beforeEach = [&]() { stack = {}; };

    it.equals("pushing when empty",
              Fn<std::list<int>>([&] {
                  stack.push(0);
                  return stack.to_std_list();
              }),
              Fn<std::list<int>>([] { return std::list{0}; }));

    it.equals("pushing when size = 1",
              Fn<std::list<int>>([&] {
                  stack = {1};
                  stack.push(0);
                  return stack.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{0, 1};
              }));

    it.equals("pushing when size > 1",
              Fn<std::list<int>>([&] {
                  stack = {1, 2, 3, 4, 5};
                  stack.push(0);
                  return stack.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{0, 1, 2, 3, 4, 5};
              }));

    it.throws("popping when empty", [&] { stack.pop(); });

    it.equals("popping when size = 1 makes stack empty",
              Fn<std::list<int>>([&] {
                  stack = {1};
                  stack.pop();
                  return stack.to_std_list();
              }),
              Fn<std::list<int>>([] { return std::list<int>{}; }));

    it.equals("popping when size = 1 returns correct value",
              Fn<int>([&] {
                  stack = {1};
                  return stack.pop();
              }),
              Fn<int>([] { return 1; }));

    it.equals("popping when size > 1 shrinks stack",
              Fn<std::list<int>>([&] {
                  stack = {1, 2, 3, 4};
                  stack.pop();
                  return stack.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{2, 3, 4};
              }));

    it.equals("popping when size > 1 returns correct value",
              Fn<int>([&] {
                  stack = {1, 2, 3, 4, 5};
                  return stack.pop();
              }),
              Fn<int>([] { return 1; }));

    it.equals("reverses a linked list",
              Fn<std::list<int>>([&] {
                  LinkedList list{1, 2, 3, 4};
                  for (auto curr{list.head}; curr != nullptr; curr = curr->next) {
                      stack.push(curr->val);
                  }
                  return stack.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{4, 3, 2, 1};
              }));

    it.exits("handles large stacks correctly", [&] {
        for (int i = 0; i < 10'000'000; i++) {
            stack.push(i);
        }
    });
}
