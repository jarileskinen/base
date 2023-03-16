#define stack_push_named_link(node, stack, next) do { \
    (stack).count++; \
    (stack).first == 0 ? \
        (stack).first = (node), (node)->next = 0 : \
        (node)->next = (stack).first, (stack).first = (node); \
} while (0)
#define stack_push(node, stack) stack_push_named_link(node, stack, next)

#define stack_pop_named_link(stack, next) do { \
    if ((stack).first) { \
        (stack).count--; \
        (stack).first = (stack).first->next; \
    } \
} while (0)
#define stack_pop(stack) stack_pop_named_link(stack, next)

