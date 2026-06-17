#include <iostream>
#include "../header/struct_func.h"

List* createEmptyList() {
    List* ls = new List{0,nullptr,nullptr};
    return ls;
}