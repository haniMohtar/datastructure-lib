#include <stdio.h>
#include "../singly_linked_list/singly_linked_list.h"

int main(void) {
    singly_linked_list* list = sll_create();

    for (int i = 0; i < 10; i++) {
        if(sll_push_back(list,i) == -1) {
            perror("push front");
            return -1;
        }
    }
    
    if (sll_print(list) == -1) {
        perror("printing");
        return -1;
    }

    sll_element_t result;

    if (sll_pop_front(list, &result) == -1) {
        perror("Could not pop");
        return -1;
    }

    printf("result = %d\n", result);

    if (sll_print(list) == -1) {
        perror("printing");
        return -1;
    }

    // printf("singly_linked_list: no tests yet\n");

    sll_destroy(&list);
    return 0;
}
