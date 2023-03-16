function inline ArenaAllocationParameters
default_arena_parameters() {
    ArenaAllocationParameters parameters;
    parameters.flags = ArenaAllocationFlag_ClearToZero;
    //parameters.alignment = 4;
    return parameters;
}

#define zero_struct(instance) memset_to_zero(&(instance), sizeof(instance))
#define zero_array(pointer, count) memset_to_zero(pointer, count*sizeof((pointer)[0]))

function inline void
memset_to_zero(void* ptr, u64 size) {
    // TODO(casey): Check this guy for performance
    u8* byte = (u8*)ptr;
    while (size--) {
        *byte++ = 0;
    }
}

#define allocate_struct(arena, type, ...) (type*)allocate_size_(arena, sizeof(type), ## __VA_ARGS__)
#define allocate_array(arena, count, type, ...) (type*)allocate_size_(arena, (count)*sizeof(type), ## __VA_ARGS__)
#define allocate_size(arena, size, ...) allocate_size_(arena, size, ## __VA_ARGS__)
#define allocate_copy(arena, size, source, ...) copy(size, source, allocate_size_(arena, size, ## __VA_ARGS__))

function inline u64
get_effective_size_for(MemoryArena* arena, u64 size_init, ArenaAllocationParameters parameters = default_arena_parameters()) {
    u64 size = size_init;
    
    // u64 AlignmentOffset = GetAlignmentOffset(arena, parameters.alignment);
    // size += AlignmentOffset;
    
    return size;
}

function inline bool
arena_has_room_for(MemoryArena* arena, u64 size_init, ArenaAllocationParameters parameters = default_arena_parameters())
{
    u64 size = get_effective_size_for(arena, size_init, parameters);
    bool result = ((arena->used + size) <= arena->size);
    return result;
}

function inline void*
allocate_size_(MemoryArena* arena, u64 size_init, ArenaAllocationParameters parameters = default_arena_parameters()) {
    if (size_init == 0) return NULL;
    
    u64 size = get_effective_size_for(arena, size_init, parameters);
    
    assert((arena->used + size) <= arena->size);
    
    // u64 AlignmentOffset = GetAlignmentOffset(arena, parameters.alignment);
    void* result = arena->base + arena->used;// + AlignmentOffset;
    arena->used += size;
    
    assert(size >= size_init);
    
    if (parameters.flags & ArenaAllocationFlag_ClearToZero) {
        memset_to_zero(result, size_init);
    }
    
    return result;
}

function inline void
initialize_arena(MemoryArena* arena, u64 size, void* base) {
    arena->size = size;
    arena->base = (u8*)base;
    arena->used = 0;
    arena->temp_count = 0;
}

function inline MemoryArena
make_memory_arena(void* base, u64 size) {
    MemoryArena result = {};
    initialize_arena(&result, size, base);
    
    return result;
}

function inline void
initialize_sub_arena(MemoryArena* sub_arena, MemoryArena* arena, u64 size, ArenaAllocationParameters parameters = default_arena_parameters()) {
    sub_arena->size = size;
    sub_arena->base = (u8*)allocate_size_(arena, size, parameters);
    sub_arena->used = 0;
    sub_arena->temp_count = 0;
}

function inline u8*
copy(void* source_init, void* dest_init, u64 size) {
    u8* source = (u8*)source_init;
    u8* dest = (u8*)dest_init;
    while (size--) {*dest++ = *source++;}
    
    return (u8*)dest_init;
}

function inline u8*
copy(MemoryArena* arena, void* source, u64 size) {
    u8* memory = allocate_array(arena, size, u8);
    copy(source, memory, size);
    
    return memory;
}

// stb.h
// optimize the small cases, though you shouldn't be calling this for those!
void swap(void* _p, void* _q, size_t size) {
    u8* p = (u8*)_p;
    u8* q = (u8*)_q;
    
    u8 buffer[256];
    if (p == q) return;
    if (size == 4) {
        u32 temp  = *(u32*) p;
        *(u32*) p = *(u32*) q;
        *(u32*) q = temp;
        return;
    }
    // else if (size == 8) {
    //    stb__8 temp    = * ( stb__8 *) p;
    //    * (stb__8 *) p = * ( stb__8 *) q;
    //    * (stb__8 *) q = temp;
    //    return;
    // }
    
    while (size > sizeof(buffer)) {
        swap(p, q, sizeof(buffer));
        p = p + sizeof(buffer);
        q = q + sizeof(buffer);
        size -= sizeof(buffer);
    }
    
    copy(p, buffer, size);
    copy(q, p, size);
    copy(buffer, q, size);
    // memcpy(buffer, p     , size);
    // memcpy(p     , q     , size);
    // memcpy(q     , buffer, size);
}

function inline u8*
get_next_memory_address(MemoryArena* arena) {
    return arena->base + arena->used;
}
