#define set_bit(field, index)       ((field) |=  (1 << (index)))
#define clear_bit(field, index)     ((field) &= ~(1 << (index)))
#define toggle_bit(field, index)    ((field) ^=  (1 << (index)))
#define is_bit_set(field, index)    ((field) &   (1 << (index)))
