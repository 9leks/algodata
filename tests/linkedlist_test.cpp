#include "datastructures/linkedlist.hpp"

#include <list>

#include "testing.hpp"

void LinkedListTest() {
    Assert it("LinkedList tests");
    LinkedList<int> list;
    std::list<int> stdlist;

    it.beforeEach = [&]() {
        list = {};
        stdlist = {};
    };

    it.equals("prepending when size = 0",
              Fn<std::list<int>>([&] {
                  list.prepend(0);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] { return std::list{0}; }));

    it.equals("prepending when size = 1",
              Fn<std::list<int>>([&] {
                  list = {1};
                  list.prepend(0);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{0, 1};
              }));

    it.equals("prepending when size > 1",
              Fn<std::list<int>>([&] {
                  list = {1, 2, 3, 4, 5};
                  list.prepend(0);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{0, 1, 2, 3, 4, 5};
              }));

    it.equals("appending when size = 0",
              Fn<std::list<int>>([&] {
                  list.append(0);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] { return std::list{0}; }));

    it.equals("appending when size = 1",
              Fn<std::list<int>>([&] {
                  list = {1};
                  list.append(2);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 2};
              }));

    it.equals("appending when size > 1",
              Fn<std::list<int>>([&] {
                  list = {1, 2, 3, 4, 5};
                  list.append(6);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 2, 3, 4, 5, 6};
              }));

    it.equals("inserting at index 0",
              Fn<std::list<int>>([&] {
                  list = {2, 3, 4, 5};
                  list.insert(1, 0);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 2, 3, 4, 5};
              }));

    it.equals("inserting at index size",
              Fn<std::list<int>>([&] {
                  list = {1, 2, 3, 4};
                  list.insert(5, list.size);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 2, 3, 4, 5};
              }));

    it.equals("inserting at index size - 1",
              Fn<std::list<int>>([&] {
                  list = {1, 2, 3, 5};
                  list.insert(4, list.size - 1);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 2, 3, 4, 5};
              }));

    it.equals("inserting at multiple indices",
              Fn<std::list<int>>([&] {
                  list = {1, 3, 6, 8, 9};
                  list.insert(2, 1);
                  list.insert(4, 3);
                  list.insert(5, 4);
                  list.insert(7, 6);
                  list.insert(-100, 5);
                  return list.to_std_list();
              }),
              Fn<std::list<int>>([] {
                  return std::list{1, 2, 3, 4, 5, -100, 6, 7, 8, 9};
              }));

    it.throws("getting when empty list throws ", Fn<void>([&] { list.get(0); }));

    it.throws("getting past list range throws", Fn<void>([&] { list.get(list.size); }));

    it.equals("getting when size = 1",
              Fn<int>([&] {
                  list = {1};
                  return list.get(0);
              }),
              Fn<int>([] { return 1; }));

    it.equals("getting when size > 1",
              Fn<int>([&] {
                  list = {1, 2, 3};
                  return list.get(1);
              }),
              Fn<int>([] { return 2; }));

    it.exits("handles large lists correctly", [&] {
        for (int i = 0; i < 10'000'000; i++) {
            list.prepend(i);
        }
    });
}
