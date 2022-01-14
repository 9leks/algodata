#include "datastructures/queue.hpp"

#include "datastructures/linkedlist.hpp"
#include "testing.hpp"

void QueueTest() {
    Assert it("Queue tests");
    Queue<int> queue;

    it.beforeEach = [&]() { queue = {}; };

    it.equals("enqueueing when empty",
              Fn<std::list<int>>([&] {
                  queue.enqueue(0);
                  return queue.to_std_list();
              }),
              Fn<std::list<int>>([] { return std::list{0}; }));

    it.equals("enqueueing when size = 1",
              Fn<std::list<int>>([&] {
                  queue = {1};
                  queue.enqueue(0);
                  return queue.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 0};
              }));

    it.equals("enqueueing when size > 1",
              Fn<std::list<int>>([&] {
                  queue = {1, 2, 3, 4, 5};
                  queue.enqueue(0);
                  return queue.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 2, 3, 4, 5, 0};
              }));

    it.throws("dequeueing when empty", [&] { queue.dequeue(); });

    it.equals("dequeueing when size = 1 makes queue empty",
              Fn<std::list<int>>([&] {
                  queue = {1};
                  queue.dequeue();
                  return queue.to_std_list();
              }),
              Fn<std::list<int>>([] { return std::list<int>{}; }));

    it.equals("dequeueing when size = 1 returns correct value",
              Fn<int>([&] {
                  queue = {1};
                  return queue.dequeue();
              }),
              Fn<int>([] { return 1; }));

    it.equals("dequeueing when size > 1 shrinks queue",
              Fn<std::list<int>>([&] {
                  queue = {1, 2, 3, 4};
                  queue.dequeue();
                  return queue.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{2, 3, 4};
              }));

    it.equals("dequeueing when size > 1 returns correct value",
              Fn<int>([&] {
                  queue = {1, 2, 3, 4, 5};
                  return queue.dequeue();
              }),
              Fn<int>([] { return 1; }));

    it.equals("copies a linked list",
              Fn<std::list<int>>([&] {
                  LinkedList list{1, 2, 3, 4};
                  for (auto curr{list.head}; curr != nullptr; curr = curr->next) {
                      queue.enqueue(curr->val);
                  }
                  return queue.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 2, 3, 4};
              }));

    it.exits("handles large queues correctly", [&] {
        for (int i{0}; i < 10'000'000; i++) {
            queue.enqueue(i);
        }
    });
}
