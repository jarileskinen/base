function u64
get_file_size(FILE* file) {
    fpos_t stored_position;
    fgetpos(file, &stored_position);
    fseek(file, 0, SEEK_END);
    u64 size = ftell(file);
    fsetpos(file, &stored_position);
    
    return size;
}

function u64
get_file_size(char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (!file) return 0;
    
    u64 size = get_file_size(file);
    fclose(file);
    
    return size;
}

function void
write_to_file(char* filename, char* contents) {
    FILE* file = fopen(filename, "w");
    u32 num_bytes = (u32)strlen(contents);
    fwrite(contents, 1, num_bytes, file);
    fclose(file);
}

function String
get_file_name_of_path(char* file_path_c_str) {
    String file_path = make_string(file_path_c_str);
    
    if (!is_char_in_set('/', file_path_c_str)) {
        return file_path;
    }
    
    u32 start_index = reverse_search(file_path, '/') + 1;
    String file_name = make_string(file_path, start_index, file_path.length - start_index);
    
    return file_name;
}

function File
read_file(MemoryArena* arena, char* file_path) {
    File file = {};
    
    FILE* file_handle = fopen(file_path, "r");
    if (!file_handle) {
        return file;
    }
    
    file.name = get_file_name_of_path(file_path);
    
    fseek(file_handle, 0, SEEK_END);
    size_t file_size = ftell(file_handle);
    fseek(file_handle, 0, SEEK_SET);
    
    file.contents = allocate_array(arena, file_size, u8);
    file.size = file_size;
    
    fread(file.contents, file.size, 1, file_handle);
    fclose(file_handle);
    
    return file;
}