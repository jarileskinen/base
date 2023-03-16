function char*
sprintf(MemoryArena* arena, const char* format_string, ...) {
    char *return_string = (char*)arena->base + arena->used;
    
    va_list args;
    va_start(args, format_string);
    s32 num_chars_written = stbsp_vsnprintf((char*)arena->base + arena->used, (int)(arena->size - arena->used), format_string, args);
    arena->used += num_chars_written + 1;
    va_end(args);
    
    return return_string;
}

#if 0
function char*
sprintf(MemoryArena* arena, const unsigned char* format_string, ...) {
    char *return_string = (char*)arena->base + arena->used;
    
    va_list args;
    va_start(args, format_string);
    s32 num_chars_written = stbsp_vsnprintf((char*)arena->base + arena->used, (int)(arena->size - arena->used), (const char*)format_string, args);
    arena->used += num_chars_written + 1;
    va_end(args);
    
    return return_string;
}
#endif

function char*
sprintf(MemoryArena* arena, char* format_string, va_list args) {
    char *return_string = (char*)arena->base + arena->used;
    
    s32 num_chars_written = stbsp_vsnprintf((char*)arena->base + arena->used, (int)(arena->size - arena->used), format_string, args);
    arena->used += num_chars_written + 1;
    
    return return_string;
}

function inline String
make_string(char* string) {
    String result = {};
    result.data = string;
    result.length = (s32)strlen(string);
    
    return result;
}
function inline String
make_string(char* string, u32 length) {
    String result = {};
    result.data = string;
    result.length = length;
    
    return result;
}

function inline String
make_string(char* string, u32 start_index, u32 end_index) {
    String result = {};
    result.data = string + start_index;
    result.length = end_index - start_index;
    
    return result;
}

function inline String
make_string(String string, u32 start_index, u32 end_index) {
    String result = {};
    result.data = string.data + start_index;
    result.length = end_index - start_index;
    
    return result;
}

function inline String
make_string(MemoryArena* arena, char* format_string, ...) {
    String result;
    
    va_list args;
    va_start(args, format_string);
    result.data = sprintf(arena, format_string, args);
    va_end(args);
    result.length = (s32)strlen(result.data);
    
    return result;
}

function inline String*
allocate_string(MemoryArena* arena, char* string) {
    String* result = allocate_struct(arena, String);
    *result = make_string(string);
    
    return result;
}
function inline String*
allocate_string(MemoryArena* arena, char* string, u32 length) {
    String* result = allocate_struct(arena, String);
    *result = make_string(string, length);
    
    return result;
}

function inline String*
allocate_string(MemoryArena* arena, char* string, u32 start_index, u32 end_index) {
    String* result = allocate_struct(arena, String);
    *result = make_string(string, start_index, end_index);
    
    return result;
}

function inline String*
allocate_string(MemoryArena* arena, String string, u32 start_index, u32 end_index) {
    String* result = allocate_struct(arena, String);
    *result = make_string(string, start_index, end_index);
    
    return result;
}

function inline char*
make_c_string(MemoryArena* arena, String string) {
    char* result = sprintf(arena, "%.*s", string.length, string.data);
    
    return result;
}

function inline String
copy(MemoryArena* arena, String string) {
    String new_string = {};
    new_string.data = (char*)copy(arena, string.data, string.length);
    new_string.length = string.length;
    
    return new_string;
}

function bool
is_char_in_set(char character, char* set) {
    u32 i = 0;
    while (set[i]) {
        if (character == set[i]) {
            return true;
        }
        
        i++;
    }
    
    return false;
}

function StringList
split(MemoryArena* arena, char* string, char* delimiters) {
    StringList strings = {};
    
    if (!string) {
        return strings;
    }
    
    u32 i = 0;
    u32 string_start_index = 0;
    while (string[i]) {
        if (is_char_in_set(string[i], delimiters)) {
            String* new_string = allocate_string(arena, string, string_start_index, i);
            dll_push_back(strings, new_string);
            string_start_index = i + 1;
        }
        
        i++;
    }
    
    String* new_string = allocate_string(arena, string, string_start_index, i);
    dll_push_back(strings, new_string);
    
    return strings;
}

function String
join(MemoryArena* arena, StringList strings, char* join_string) {
    String result = {};
    
    if (!strings.count) {
        return result;
    }
    
    u32 join_string_length = (u32)strlen(join_string);
    result.length = join_string_length * (strings.count - 1);
    result.data = (char*)get_next_memory_address(arena);
    
    String* it;
    for_linked_list (it, strings) {
        sprintf(arena, "%.*s%s", it->length, it->data, join_string);
        arena->used--;
        
        result.length += it->length;
    }
    
    arena->used -= join_string_length;
    
    return result;
}

function bool
compare(String string1, String string2) {
    if (!string1.data || !string2.data) return false;
    if (string1.length != string2.length) return false;
    
    u64 i;
    for_range (i, 0, string1.length) {
        if (string1.data[i] != string2.data[i]) {
            return false;
        }
    }
    
    return true;
}

function bool
compare(String string1, char* string2) {
    if (!string1.data || !string2) return false;
    if (string1.length != strlen(string2)) return false;
    
    u64 i;
    for_range (i, 0, string1.length) {
        if (string1.data[i] != string2[i]) {
            return false;
        }
    }
    
    return true;
}

function bool
compare(char* string1, String string2) {
    return compare(string2, string1);
}

function String
trim_leading_whitespace(String string) {
    while (string.length) {
        if (!isspace(string.data[0])) break;
        
        string.data++;
        string.length--;
    }
    
    return string;
}

function String
trim_trailing_whitespace(String string) {
    while (string.length) {
        if (!isspace(string.data[string.length - 1])) break;
        
        string.length--;
    }
    
    return string;
}

function String
to_lowercase(MemoryArena* arena, String string) {
    String result = copy(arena, string);
    
    s32 i;
    for_range (i, 0, result.length) {
        result.data[i] = (char)tolower(result.data[i]);
    }
    
    return result;
}

function String
to_uppercase(MemoryArena* arena, String string) {
    String result = copy(arena, string);
    
    s32 i;
    for_range (i, 0, result.length) {
        result.data[i] = (char)toupper(result.data[i]);
    }
    
    return result;
}

function u32
search(String string, char character) {
    s32 i;
    for_range (i, 0, string.length) {
        if (string.data[i] == character) {
            return i;
        }
    }
    
    return string.length;
}

function u32
reverse_search(String string, char character) {
    for (s32 i = string.length - 1; i >= 0; i--) {
        if (string.data[i] == character) {
            return i;
        }
    }
    
    return string.length;
}

#if 0
function String
find_next_whitespace(String string) {
    while (string.length) {
        if (isspace(string.data[0])) {
            return string;
        }
        
        string.data++;
        string.length--;
    }
    
    return string;
}

function String
find_next_non_whitespace(String string) {
    while (string.length) {
        if (!isspace(string.data[0])) {
            return string;
        }
        
        string.data++;
        string.length--;
    }
    
    return string;
}
#endif
