#include "linkedlists/queue.hpp"

#include "linkedlists/linkedlist.hpp"
#include "testing.hpp"

void QueueTest() {
    Assert it("Queue tests");
    Queue<int> queue;

    it.beforeEach = [&]() { queue = {}; };

    it.exits("copy assignment operator", [] { Queue<int> copy; });

    it.exits("copy constructor", [&] {
        queue = {1, 2, 3};
        auto copy = queue;

        if (copy != queue) {
            it.raise();
        }

        copy.enqueue(-1);

        if (copy == queue) {
            it.raise();
        }
    });

    it.exits("move constructor", [&] {
        queue = {1, 2, 3};
        auto copy = std::move(queue);
        if (!queue.is_empty()) {
            it.raise();
        }
    });

    it.exits("swapping", [&] {
        queue = {1, 2, 3};
        auto other = queue;
        other.enqueue(-1);
        std::swap(queue, other);

        if (queue != Queue{1, 2, 3, -1} || queue.size != 4) {
            it.raise();
        }

        other.dequeue();
        if (other != Queue{2, 3} || other.size != 2) {
            it.raise();
        }
    });

    it.exits("handles large lists correctly", [&] {
        for (int i = 0; i < 10'000'000; i++) {
            queue.enqueue(i);
        }
    });

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
}
