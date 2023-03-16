#define queue_push_named_link(node, queue, next) do { \
    (queue).count++; \
    (queue).first == 0 ? \
        (queue).first = (queue).last = (node), (node)->next = 0 : \
        (queue).last->next = (node), (queue).last = (node), (node)->next = 0; \
} while (0)
#define queue_push(node, queue) queue_push_named_link(node, queue, next)

#define queue_push_front_named_link(node, queue, next) do { \
    (queue).count++; \
    (queue).first == 0 ? \
        (queue).first = (queue).last = (node), (node)->next = 0 : \
        (node)->next = (queue).first, (queue).first = (node); \
} while (0)
#define queue_push_front(node, queue) queue_push_front_named_link(node, queue, next)

#define queue_pop_named_link(queue, next) do { \
    (queue).count--; \
    (queue).first == (queue).last ? \
        (queue).first = (queue).last = 0 : \
        (queue).first = (queue).first->next; \
} while (0)
#define queue_pop(queue) queue_pop_named_link(queue, next)

