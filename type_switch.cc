//
// Created by suun on 11/5/19.
//

#include "type_switch.h"

void testTypeSwitch() {
  std::vector<Animal *> v = {new Cat, new Dog};
  for (Animal *animal : v) {
    type_switch(
        animal,
        [](Cat *cat) {
          printf("this is cat\n");
        },
        [](Dog *dog) {
          printf("this is dog\n");
        }
    );
  }
}
