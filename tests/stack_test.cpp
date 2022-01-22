#include "linkedlists/stack.hpp"

#include <list>

#include "linkedlists/linkedlist.hpp"
#include "testing.hpp"

void StackTest() {
    Assert it("Stack tests");
    Stack<int> stack;

    it.beforeEach = [&]() { stack = {}; };

    it.exits("copy assignment operator", [] { Stack<int> copy; });

    it.exits("copy constructor", [&] {
        stack = {1, 2, 3};
        auto copy = stack;

        if (copy != stack) {
            it.raise();
        }

        copy.push(-1);

        if (copy == stack) {
            it.raise();
        }
    });

    it.exits("move constructor", [&] {
        stack = {1, 2, 3};
        auto copy = std::move(stack);
        if (!stack.is_empty()) {
            it.raise();
        }
    });

    it.exits("swapping", [&] {
        stack = {1, 2, 3};
        auto other = stack;
        other.push(-1);
        std::swap(stack, other);

        if (stack != Stack<int>{-1, 1, 2, 3} || stack.size != 4) {
            it.raise();
        }

        if (other != Stack<int>{1, 2, 3} || other.size != 3) {
            it.raise();
        }
    });

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

    it.equals("reverses a linked stack",
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
}
