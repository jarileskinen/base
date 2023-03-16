struct String {
    char* data;
    s32 length;
    String* next;
    String* previous;
    
    String* reversed_next;
    String* reversed_previous;
};

struct StringList {
    String* first;
    String* last;
    u32 count;
};

struct MemoryArena {
    u64 size;
    u8* base;
    u64 used;
    
    s32 temp_count;
};

struct TemporaryMemory {
    MemoryArena* arena;
    u64 used;
};

enum ArenaAllocationFlag {
    ArenaAllocationFlag_ClearToZero = 0x1,
};
struct ArenaAllocationParameters {
    u32 flags;
    u32 alignment;
};

struct File {
    String name;
    u8* contents;
    s64 size;
};
