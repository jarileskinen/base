#define dll_push_back_np(first, last, node, next, previous) ((first)==0?\
((first)=(last)=(node),(node)->next=(node)->previous=0):\
((node)->previous=(last),(last)->next=(node),(last)=(node),(node)->next=0))

#define _dll_push_back(list, node, next, previous) \
do { \
(list).count++; \
dll_push_back_np((list).first, (list).last, node, next, previous); \
} while (0)

#define dll_push_back(list, node) _dll_push_back(list, node, next, previous)
#define dll_push_back_named_links(list, node, next, previous) _dll_push_back(list, node, next, previous)

#define _dll_push_front(list, node, next, previous) \
do { \
(list).count++; \
dll_push_back_np((list).last, (list).first, node, previous, next); \
} while (0)

#define dll_push_front(list, node) _dll_push_front(list, node, next, previous)
#define dll_push_front_named_links(list, node, next, previous) _dll_push_front(list, node, next, previous)

#define dll_remove_np(first, last, node, next, previous) (((first)==(node)?\
((first)=(first)->next, ((first) ? (first)->previous=0:(last)=0)):\
(last)==(node)?\
((last)=(last)->previous,(last)->next=0):\
((node)->next->previous=(node)->previous,\
(node)->previous->next=(node)->next)))

#define _dll_remove(list, node, next, previous) \
do { \
(list).count--; \
dll_remove_np((list).first, (list).last, node, next, previous); \
} while (0)
#define dll_remove(list, node) _dll_remove(list, node, next, previous)

#define for_linked_list_named_link(it, list, next) for (it = (list).first; it; it = it->next)
#define for_linked_list(it, list) for_linked_list_named_link(it, list, next)
#define for_linked_list_reversed_named_link(it, list, previous) for (it = (list).last; it; it = it->previous)
#define for_linked_list_reversed(it, list) for_linked_list_reversed_named_link(it, list, previous)
